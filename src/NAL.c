#include "NAL.h"
//macro for syntactic representation, increases readability
#define R(premise1, premise2, _, conclusion, truthFunction) NAL_GenerateRule(#premise1, #premise2, #conclusion, #truthFunction);

int ruleID = 0;
static void NAL_GeneratePremisesUnifier(int i, Atom atom, int premiseIndex)
{
    if(atom)
    {
        //upper case atoms are treated as variables in the meta rule language
        if(atom_names[atom-1][0] >= 'A' && atom_names[atom-1][0] <= 'Z')
        {
            //unification failure by inequal value assignment (value at position i versus previously assigned one), and variable binding
            printf("subtree = Term_ExtractSubterm(&term%d, %d);\n", premiseIndex, i);
            printf("if(substitutions[%d].atoms[0]!=0 && !Term_Equal(&substitutions[%d], &subtree)){ goto RULE_%d; }\n", atom, atom, ruleID);
            printf("substitutions[%d] = subtree;\n", atom);
        }
        else
        {
            //structural constraint given by copulas at position i
            printf("if(term%d.atoms[%d] != %d){ goto RULE_%d; }\n", premiseIndex, i, atom, ruleID);
        }
    }
}

static void NAL_GenerateConclusionSubstitution(int i, Atom atom)
{
    if(atom)
    {
        if(atom_names[atom-1][0] >= 'A' && atom_names[atom-1][0] <= 'Z')
        {
            //conclusion term gets variables substituted
            //printf("assert(substitutions[%d]>0,\"Meta variable was not substituted, check inference rule!\");\n", atom);
            printf("Term_OverrideSubterm(&conclusion,%d,&substitutions[%d]);\n", i, atom);
        }
        else
        {
            //conclusion term inherits structure from meta rule, namely the copula
            printf("conclusion.atoms[%d] = %d;\n", i, atom);
        }
    }
}

static void NAL_GenerateRule(char *premise1, char *premise2, char* conclusion, char* truthFunction)
{
    Term term1 = Encode_Term(premise1);
    Term term2 = Encode_Term(premise2);
    Term conclusion_term = Encode_Term(conclusion);
    printf("RULE_%d:\n{\n",ruleID++);
    puts("Term substitutions[255] = {0}; Term subtree = {0};");
    for(int i=0; i<COMPOUND_TERM_SIZE_MAX; i++)
    {
        NAL_GeneratePremisesUnifier(i, term1.atoms[i], 1);
    }
    for(int i=0; i<COMPOUND_TERM_SIZE_MAX; i++)
    {
        NAL_GeneratePremisesUnifier(i, term2.atoms[i], 2);
    }
    puts("Term conclusion = {0};");
    for(int i=0; i<COMPOUND_TERM_SIZE_MAX; i++)
    {
        NAL_GenerateConclusionSubstitution(i, conclusion_term.atoms[i]);
    }
    printf("Truth conclusionTruth = %s(truth1,truth2);\n", truthFunction);
    puts("NAL_DerivedEvent(conclusion, conclusionOccurrence, conclusionTruth, conclusionStamp, currentTime);");
    puts("}");
}

void NAL_GenerateRuleTable()
{
    puts("#include \"RuleTable.h\"");
    puts("void RuleTable_Apply(Term term1, Term term2, Truth truth1, Truth truth2, long conclusionOccurrence, Stamp conclusionStamp, long currentTime)\n{\ngoto RULE_0;");
#define H_NAL_RULES
#include "NAL.h"
#undef H_NAL_RULES
    printf("RULE_%d:;\n}\n", ruleID);
}

void NAL_DerivedEvent(Term conclusionTerm, long conclusionOccurrence, Truth conclusionTruth, Stamp stamp, long currentTime)
{
    Event e = { .term = conclusionTerm,
                .type = EVENT_TYPE_BELIEF, 
                .truth = conclusionTruth, 
                .stamp = stamp,
                .occurrenceTime = conclusionOccurrence };
    Memory_addEvent(&e, currentTime, false, true);
}