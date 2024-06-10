pub const root = @import("root.zig");

pub export fn main(arg_argc: c_int, arg_argv: [*c][*c]u8) c_int {
    var argc = arg_argc;
    _ = &argc;
    var argv = arg_argv;
    _ = &argv;
    root.mysrand(@as(c_uint, @bitCast(@as(c_int, 666))));
    root.Process_Args(argc, argv);
    if (argc == @as(c_int, 1)) {
        root.NAR_INIT();
        root.Run_Unit_Tests();
        root.Run_System_Tests();
        root.Display_Help();
    }
    return 0;
}
