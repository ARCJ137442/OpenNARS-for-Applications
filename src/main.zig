pub const root = @import("root.zig");

pub export fn Process_Args(arg_argc: c_int, arg_argv: [*c][*c]u8) void {
    var argc = arg_argc;
    _ = &argc;
    var argv = arg_argv;
    _ = &argv;
    var inspectionOnExit: bool = @as(c_int, 0) != 0;
    _ = &inspectionOnExit;
    var iterations: c_long = @as(c_long, @bitCast(@as(c_long, -@as(c_int, 1))));
    _ = &iterations;
    if (argc >= @as(c_int, 4)) {
        if (!(root.strcmp(argv[@as(c_uint, @intCast(@as(c_int, 3)))], "InspectionOnExit") != 0)) {
            inspectionOnExit = @as(c_int, 1) != 0;
        }
    }
    if (argc >= @as(c_int, 3)) {
        if (!(root.strcmp(argv[@as(c_uint, @intCast(@as(c_int, 2)))], "InspectionOnExit") != 0)) {
            inspectionOnExit = @as(c_int, 1) != 0;
        }
    }
    if (argc >= @as(c_int, 2)) {
        root.NAR_INIT();
        if (!(root.strcmp(argv[@as(c_uint, @intCast(@as(c_int, 1)))], "NAL_GenerateRuleTable") != 0)) {
            root.NAL_GenerateRuleTable();
            root.exit(@as(c_int, 0));
        }
        if (!(root.strcmp(argv[@as(c_uint, @intCast(@as(c_int, 1)))], "shell") != 0)) {
            root.Shell_Start();
        }
        {
            var i: c_int = 1;
            _ = &i;
            while (i < argc) : (i += 1) {
                iterations = if ((i + @as(c_int, 1)) < argc) root.atol((blk: {
                    const tmp = i + @as(c_int, 1);
                    if (tmp >= 0) break :blk argv + @as(usize, @intCast(tmp)) else break :blk argv - ~@as(usize, @bitCast(@as(isize, @intCast(tmp)) +% -1));
                }).*) else @as(c_long, @bitCast(@as(c_long, -@as(c_int, 1))));
                if (!(root.strcmp((blk: {
                    const tmp = i;
                    if (tmp >= 0) break :blk argv + @as(usize, @intCast(tmp)) else break :blk argv - ~@as(usize, @bitCast(@as(isize, @intCast(tmp)) +% -1));
                }).*, "pong") != 0)) {
                    root.NAR_Pong(iterations);
                } else if (!(root.strcmp((blk: {
                    const tmp = i;
                    if (tmp >= 0) break :blk argv + @as(usize, @intCast(tmp)) else break :blk argv - ~@as(usize, @bitCast(@as(isize, @intCast(tmp)) +% -1));
                }).*, "pong2") != 0)) {
                    root.NAR_Pong2(iterations);
                } else if (!(root.strcmp((blk: {
                    const tmp = i;
                    if (tmp >= 0) break :blk argv + @as(usize, @intCast(tmp)) else break :blk argv - ~@as(usize, @bitCast(@as(isize, @intCast(tmp)) +% -1));
                }).*, "testchamber") != 0)) {
                    root.NAR_TestChamber();
                } else if (!(root.strcmp((blk: {
                    const tmp = i;
                    if (tmp >= 0) break :blk argv + @as(usize, @intCast(tmp)) else break :blk argv - ~@as(usize, @bitCast(@as(isize, @intCast(tmp)) +% -1));
                }).*, "alien") != 0)) {
                    root.NAR_Alien(iterations);
                } else if (!(root.strcmp((blk: {
                    const tmp = i;
                    if (tmp >= 0) break :blk argv + @as(usize, @intCast(tmp)) else break :blk argv - ~@as(usize, @bitCast(@as(isize, @intCast(tmp)) +% -1));
                }).*, "cartpole") != 0)) {
                    root.NAR_Cartpole(iterations);
                } else if (!(root.strcmp((blk: {
                    const tmp = i;
                    if (tmp >= 0) break :blk argv + @as(usize, @intCast(tmp)) else break :blk argv - ~@as(usize, @bitCast(@as(isize, @intCast(tmp)) +% -1));
                }).*, "robot") != 0)) {
                    root.NAR_Robot(iterations);
                } else if (!(root.strcmp((blk: {
                    const tmp = i;
                    if (tmp >= 0) break :blk argv + @as(usize, @intCast(tmp)) else break :blk argv - ~@as(usize, @bitCast(@as(isize, @intCast(tmp)) +% -1));
                }).*, "bandrobot") != 0)) {
                    root.NAR_Bandrobot(iterations);
                }
            }
        }
    }
    if (inspectionOnExit) {
        _ = root.Shell_ProcessInput(@as([*c]u8, @ptrCast(@volatileCast(@constCast("*opconfig")))));
        _ = root.Shell_ProcessInput(@as([*c]u8, @ptrCast(@volatileCast(@constCast("*concepts")))));
        _ = root.Shell_ProcessInput(@as([*c]u8, @ptrCast(@volatileCast(@constCast("*cycling_belief_events")))));
        _ = root.Shell_ProcessInput(@as([*c]u8, @ptrCast(@volatileCast(@constCast("*cycling_goal_events")))));
        _ = root.Shell_ProcessInput(@as([*c]u8, @ptrCast(@volatileCast(@constCast("*stats")))));
    }
}
pub export fn Display_Help() void {
    _ = root.puts("\nAll C tests ran successfully, run python3 evaluation.py for more comprehensive evaluation!");
    _ = root.puts("");
    _ = root.puts("Welcome to `OpenNARS for Applications`!");
    _ = root.puts("```````````````````````````````````````");
    _ = root.puts(" __        ");
    _ = root.puts("/ \\`-+-.__ ");
    _ = root.puts("```  |  /o\\");
    _ = root.puts("     |  ```");
    _ = root.puts("  __/ \\__  ");
    _ = root.puts("  ```````  ");
    _ = root.puts("If you wish to run examples now, just pass the corresponding parameter:");
    _ = root.puts("NAR pong (starts Pong example)");
    _ = root.puts("NAR pong2 (starts Pong2 example)");
    _ = root.puts("NAR testchamber (starts Test Chamber multistep procedure learning example)");
    _ = root.puts("NAR alien (starts the alien example)");
    _ = root.puts("NAR cartpole (starts the cartpole example)");
    _ = root.puts("NAR bandrobot (starts the band robot example)");
    _ = root.puts("NAR robot (starts the grid robot example)");
    _ = root.puts("NAR shell (starts the interactive NAL shell)");
}
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
