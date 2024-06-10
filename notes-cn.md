# ONA-zig 开发笔记

## ️📝安装配置zig工具链

参考资料：

- zig教程1（含环境变量配置）：<https://course.ziglang.cc/>
- zig教程2：<https://learn.ziglang.cc/01-installing-zig.html>
- 下载zig：<https://ziglang.org/download/>
- zig VSCode扩展：扩展市场搜索「zig」

## 未解决依赖问题：UDP/网络相关

❓【2024-06-10 11:13:13】尚且不会引入外部头文件，导致无法编译

参考资料：

- <https://blog.csdn.net/zhenz0729/article/details/138120785>
  - ❌VSCode可能不是用GCC编译的
  - ❌运行`gcc -v -E -x C -`报错：`gcc: error: language C not recognized`

🚩【2024-06-10 11:15:11】目前措施：移除「依赖外部库的代码」，仅保留内核

## 未解决：依赖于cygwin的SLEEP编译错误

❓【2024-06-10 11:55:49】尚且不会解决头文件缺失问题：缺少`nanosleep`函数

🚩【2024-06-10 11:56:12】目前措施：将`SLEEP`宏取消掉定义（空语句）

参考资料：

- <https://blog.csdn.net/qq_29296283/article/details/131360020>

## Zig转换 `translate-c`

⚠️需要引入标准库libc：`zig translate-c [文件] -lc`

参考资料：

- 编译选项介绍：<https://fig.io/manual/zig/translate-c>
- <https://blog.csdn.net/withstand/article/details/130134386>
- <https://github.com/ziglang/zig/issues/2488>
- <https://www.reddit.com/r/Zig/comments/leuypm/trouble_compiling_on_windows_with_c_library/>
- <https://www.reddit.com/r/Zig/comments/d5qceu/1st_attempt_at_translatec_fails/>

## 编译时代码生成问题：缺少`RuleTable.c`

📝ONA中的「规则表」代码是在构建脚本中自动生成的

💡ONA的构建后文件提供了生成`RuleTable.c`的功能

✅解决：找到一个已构建好的`NAR.exe`，运行命令：

```bash
NAR.exe NAL_GenerateRuleTable > RuleTable.c
```

🚩将生成的C代码放入`src`目录中

## 未解决：代码可转换，但存在诸多依赖问题，【项目不可用】

⚠️可使用 `zig translate-c src/main.c -lc > src/main.zig` 命令转换，但有143处@compileError

💭原C版本亦尚未有成功编译之经验，何谈转换？

### 所有编译错误，截止至【2024-06-10 12:18:49】

- `pub const __mingw_printf = @compileError("unable to resolve function type clang.TypeClass.MacroQualified");`
- `pub const __mingw_vprintf = @compileError("unable to resolve function type clang.TypeClass.MacroQualified");`
- `pub const __mingw_fprintf = @compileError("unable to resolve function type clang.TypeClass.MacroQualified");`
- `pub const __mingw_vfprintf = @compileError("unable to resolve function type clang.TypeClass.MacroQualified");`
- `pub const __mingw_sprintf = @compileError("unable to resolve function type clang.TypeClass.MacroQualified");`
- `pub const __mingw_vsprintf = @compileError("unable to resolve function type clang.TypeClass.MacroQualified");`
- `pub const __mingw_asprintf = @compileError("unable to resolve function type clang.TypeClass.MacroQualified");`
- `pub const __mingw_vasprintf = @compileError("unable to resolve function type clang.TypeClass.MacroQualified");`
- `pub const __ms_printf = @compileError("unable to resolve function type clang.TypeClass.MacroQualified");`
- `pub const __ms_vprintf = @compileError("unable to resolve function type clang.TypeClass.MacroQualified");`
- `pub const __ms_fprintf = @compileError("unable to resolve function type clang.TypeClass.MacroQualified");`
- `pub const __ms_vfprintf = @compileError("unable to resolve function type clang.TypeClass.MacroQualified");`
- `pub const __ms_sprintf = @compileError("unable to resolve function type clang.TypeClass.MacroQualified");`
- `pub const __ms_vsprintf = @compileError("unable to resolve function type clang.TypeClass.MacroQualified");`
- `pub const _beep = @compileError("unable to resolve function type clang.TypeClass.MacroQualified");`
- `pub const _seterrormode = @compileError("unable to resolve function type clang.TypeClass.MacroQualified");`
- `pub const _sleep = @compileError("unable to resolve function type clang.TypeClass.MacroQualified");`
- `pub const __INTMAX_C_SUFFIX__ = @compileError("unable to translate macro: undefined identifier`LL`");`
- `pub const __UINTMAX_C_SUFFIX__ = @compileError("unable to translate macro: undefined identifier`ULL`");`
- `pub const __INT64_C_SUFFIX__ = @compileError("unable to translate macro: undefined identifier`LL`");`
- `pub const __UINT32_C_SUFFIX__ = @compileError("unable to translate macro: undefined identifier`U`");`
- `pub const __UINT64_C_SUFFIX__ = @compileError("unable to translate macro: undefined identifier`ULL`");`
- `pub const __seg_gs = @compileError("unable to translate macro: undefined identifier`address_space`");`
- `pub const __seg_fs = @compileError("unable to translate macro: undefined identifier`address_space`");`
- `pub const __declspec = @compileError("unable to translate C expr: unexpected token '__attribute__'");`
- `pub const _cdecl = @compileError("unable to translate macro: undefined identifier`__cdecl__`");`
- `pub const __cdecl = @compileError("unable to translate macro: undefined identifier`__cdecl__`");`
- `pub const _stdcall = @compileError("unable to translate macro: undefined identifier`__stdcall__`");`
- `pub const __stdcall = @compileError("unable to translate macro: undefined identifier`__stdcall__`");`
- `pub const _fastcall = @compileError("unable to translate macro: undefined identifier`__fastcall__`");`
- `pub const __fastcall = @compileError("unable to translate macro: undefined identifier`__fastcall__`");`
- `pub const _thiscall = @compileError("unable to translate macro: undefined identifier`__thiscall__`");`
- `pub const __thiscall = @compileError("unable to translate macro: undefined identifier`__thiscall__`");`
- `pub const _pascal = @compileError("unable to translate macro: undefined identifier`__pascal__`");`
- `pub const __pascal = @compileError("unable to translate macro: undefined identifier`__pascal__`");`
- `pub const __STRINGIFY = @compileError("unable to translate C expr: unexpected token '#'");`
- `pub const __MINGW_IMP_SYMBOL = @compileError("unable to translate macro: undefined identifier`__imp_`");`
- `pub const __MINGW_IMP_LSYMBOL = @compileError("unable to translate macro: undefined identifier`__imp_`");`
- `pub const __MINGW_LSYMBOL = @compileError("unable to translate C expr: unexpected token '##'");`
- `pub const __MINGW_ASM_CALL = @compileError("unable to translate C expr: unexpected token '__asm__'");`
- `pub const __MINGW_ASM_CRT_CALL = @compileError("unable to translate C expr: unexpected token '__asm__'");`
- `pub const __MINGW_EXTENSION = @compileError("unable to translate C expr: unexpected token '__extension__'");`
- `pub const __MINGW_POISON_NAME = @compileError("unable to translate macro: undefined identifier`_layout_has_not_been_verified_and_its_declaration_is_most_likely_incorrect`");`
- `pub const __MINGW_ATTRIB_DEPRECATED_STR = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __MINGW_MS_PRINTF = @compileError("unable to translate macro: undefined identifier`__format__`");`
- `pub const __MINGW_MS_SCANF = @compileError("unable to translate macro: undefined identifier`__format__`");`
- `pub const __MINGW_GNU_PRINTF = @compileError("unable to translate macro: undefined identifier`__format__`");`
- `pub const __MINGW_GNU_SCANF = @compileError("unable to translate macro: undefined identifier`__format__`");`
- `pub const __mingw_ovr = @compileError("unable to translate macro: undefined identifier`__unused__`");`
- `pub const __mingw_attribute_artificial = @compileError("unable to translate macro: undefined identifier`__artificial__`");`
- `pub const __MINGW_SELECTANY = @compileError("unable to translate macro: undefined identifier`__selectany__`");`
- `pub const __MINGW_CRT_NAME_CONCAT2 = @compileError("unable to translate macro: undefined identifier`_s`");`
- `pub const __CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY_0_3_ = @compileError("unable to translate C expr: unexpected token ';'");`
- `pub const __MINGW_IMPORT = @compileError("unable to translate macro: undefined identifier`__dllimport__`");`
- `pub const _CRTIMP = @compileError("unable to translate macro: undefined identifier`__dllimport__`");`
- `pub const _inline = @compileError("unable to translate C expr: unexpected token '__inline'");`
- `pub const __CRT_INLINE = @compileError("unable to translate macro: undefined identifier`__gnu_inline__`");`
- `pub const __MINGW_INTRIN_INLINE = @compileError("unable to translate macro: undefined identifier`__always_inline__`");`
- `pub const __UNUSED_PARAM = @compileError("unable to translate macro: undefined identifier`__unused__`");`
- `pub const __restrict_arr = @compileError("unable to translate C expr: unexpected token '__restrict'");`
- `pub const __MINGW_ATTRIB_NORETURN = @compileError("unable to translate macro: undefined identifier`__noreturn__`");`
- `pub const __MINGW_ATTRIB_CONST = @compileError("unable to translate C expr: unexpected token '__attribute__'");`
- `pub const __MINGW_ATTRIB_MALLOC = @compileError("unable to translate macro: undefined identifier`__malloc__`");`
- `pub const __MINGW_ATTRIB_PURE = @compileError("unable to translate macro: undefined identifier`__pure__`");`
- `pub const __MINGW_ATTRIB_NONNULL = @compileError("unable to translate macro: undefined identifier`__nonnull__`");`
- `pub const __MINGW_ATTRIB_UNUSED = @compileError("unable to translate macro: undefined identifier`__unused__`");`
- `pub const __MINGW_ATTRIB_USED = @compileError("unable to translate macro: undefined identifier`__used__`");`
- `pub const __MINGW_ATTRIB_DEPRECATED = @compileError("unable to translate macro: undefined identifier`__deprecated__`");`
- `pub const __MINGW_ATTRIB_DEPRECATED_MSG = @compileError("unable to translate macro: undefined identifier`__deprecated__`");`
- `pub const __MINGW_NOTHROW = @compileError("unable to translate macro: undefined identifier`__nothrow__`");`
- `pub const __MINGW_PRAGMA_PARAM = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __MINGW_BROKEN_INTERFACE = @compileError("unable to translate macro: undefined identifier`message`");`
- `pub const __forceinline = @compileError("unable to translate macro: undefined identifier`__always_inline__`");`
- `pub const _crt_va_start = @compileError("unable to translate macro: undefined identifier`__builtin_va_start`");`
- `pub const _crt_va_arg = @compileError("unable to translate C expr: unexpected token 'an identifier'");`
- `pub const _crt_va_end = @compileError("unable to translate macro: undefined identifier`__builtin_va_end`");`
- `pub const _crt_va_copy = @compileError("unable to translate macro: undefined identifier`__builtin_va_copy`");`
- `pub const __CRT_STRINGIZE = @compileError("unable to translate C expr: unexpected token '#'");`
- `pub const __CRT_WIDE = @compileError("unable to translate macro: undefined identifier`L`");`
- `pub const _CRT_DEPRECATE_TEXT = @compileError("unable to translate macro: undefined identifier`deprecated`");`
- `pub const _CRT_INSECURE_DEPRECATE_MEMORY = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const _CRT_INSECURE_DEPRECATE_GLOBALS = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const _CRT_OBSOLETE = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const _CRT_ALIGN = @compileError("unable to translate macro: undefined identifier`__aligned__`");`
- `pub const _CRT_glob = @compileError("unable to translate macro: undefined identifier`_dowildcard`");`
- `pub const _UNION_NAME = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const _STRUCT_NAME = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __CRT_UUID_DECL = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __MINGW_PREFETCH_IMPL = @compileError("unable to translate macro: undefined identifier`__prefetch`");`
- `pub const _CRT_SECURE_CPP_NOTHROW = @compileError("unable to translate macro: undefined identifier`throw`");`
- `pub const __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0 = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1 = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2 = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3 = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4 = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1 = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_2 = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_3 = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __DEFINE_CPP_OVERLOAD_SECURE_FUNC_2_0 = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1_ARGLIST = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2_ARGLIST = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __DEFINE_CPP_OVERLOAD_SECURE_FUNC_SPLITPATH = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0 = @compileError("unable to translate macro: undefined identifier`__func_name`");`
- `pub const __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1 = @compileError("unable to translate macro: undefined identifier`__func_name`");`
- `pub const __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2 = @compileError("unable to translate macro: undefined identifier`__func_name`");`
- `pub const __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3 = @compileError("unable to translate macro: undefined identifier`__func_name`");`
- `pub const __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4 = @compileError("unable to translate macro: undefined identifier`__func_name`");`
- `pub const __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const __crt_typefix = @compileError("unable to translate C expr: unexpected token ''");`
- `pub const _SECIMP = @compileError("unable to translate macro: undefined identifier`dllimport`");`
- `pub const timerclear = @compileError("unable to translate C expr: unexpected token '='");`
- `pub const _countof = @compileError("unable to translate C expr: expected ')' instead got '['");`
- `pub const _STATIC_ASSERT = @compileError("unable to translate macro: undefined identifier`__static_assert_t`");`
- `pub const _alloca = @compileError("unable to translate macro: undefined identifier`__builtin_alloca`");`
- `pub const alloca = @compileError("unable to translate macro: undefined identifier`__builtin_alloca`");`
- `pub const IN_DEBUG = @compileError("unable to translate C expr: unexpected token '{'");`
- `pub const NUM_ELEMENTS = @compileError("unable to translate C expr: expected ')' instead got '['");`
- `pub const STR_HELPER = @compileError("unable to translate C expr: unexpected token '#'");`
- `pub const __mingw_types_compatible_p = @compileError("unable to translate C expr: unexpected token 'an identifier'");`
- `pub const __mingw_choose_expr = @compileError("unable to translate C expr: unexpected token 'an identifier'");`
- `pub const HUGE_VAL = @compileError("unable to translate macro: undefined identifier`__builtin_huge_val`");`
- `pub const HUGE_VALL = @compileError("unable to translate macro: undefined identifier`__builtin_huge_vall`");`
- `pub const fpclassify = @compileError("unable to translate macro: undefined identifier`__builtin_trap`");`
- `pub const isnan = @compileError("unable to translate macro: undefined identifier`__builtin_trap`");`
- `pub const signbit = @compileError("unable to translate macro: undefined identifier`__builtin_trap`");`
- `pub const isgreater = @compileError("unable to translate macro: undefined identifier`__builtin_isgreater`");`
- `pub const isgreaterequal = @compileError("unable to translate macro: undefined identifier`__builtin_isgreaterequal`");`
- `pub const isless = @compileError("unable to translate macro: undefined identifier`__builtin_isless`");`
- `pub const islessequal = @compileError("unable to translate macro: undefined identifier`__builtin_islessequal`");`
- `pub const islessgreater = @compileError("unable to translate macro: undefined identifier`__builtin_islessgreater`");`
- `pub const isunordered = @compileError("unable to translate macro: undefined identifier`__builtin_isunordered`");`
- `pub const R2 = @compileError("unable to translate macro: undefined identifier`NAL_GenerateRule`");`
- `pub const R2VarIntro = @compileError("unable to translate macro: undefined identifier`NAL_GenerateRule`");`
- `pub const R1 = @compileError("unable to translate macro: undefined identifier`NAL_GenerateRule`");`
- `pub const R1Bidirectional = @compileError("unable to translate macro: undefined identifier`NAL_GenerateRule`");`
- `pub const ReduceTerm = @compileError("unable to translate macro: undefined identifier`NAL_GenerateReduction`");`
- `pub const ReduceStatement = @compileError("unable to translate macro: undefined identifier`NAL_GenerateReduction`");`
- `pub const CLEAR_SCREEN = @compileError("unable to translate C expr: unexpected token 'do'");`
- `pub const BREAK_ON_DONE = @compileError("unable to translate macro: undefined identifier`ret`");`
