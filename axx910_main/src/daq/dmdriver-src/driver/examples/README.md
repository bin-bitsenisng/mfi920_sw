Driver Examples
===============

Source Files
------------

| Source File                    | Comment                                                  |
|--------------------------------|----------------------------------------------------------|
| example_dma_ramp.c             | Full example transmitting ramps using DMA mode.          |
| example_tasklist.c             | A functionally equivalent example using tasklists.       |
| example_syscal.c               | Example of system calibration and t0 measurement.        |
| example_init.c                 | Common initialization routine used by all examples.      |
| example_burst_loop.c           | Measurement loop routine used by example_dma_ramp.c.     |
| example_main.c                 | A main() to call the examples.                           |
| application.h                  | Declarations for the examples.                           |
| example_burst_loop.c           | Measurement loop routine used by example_dma_ramp.c.     |
| tasklist_util.c                | Utilities for building tasklists.                        |
| tasklist_util.h                | Header file for utilities for building tasklists.        |
| f2decl.c                       | Utility to convert binary file to C initialization.      |
| platforms/win/*                | Files to build the example with Visual Studio on Windows |
| platforms/win/example.sln      | *VisualStudio* Solution file to build example and driver |
| platforms/win/dummy_hal.c      | Stub @ref HAL routines                                   |
| platforms/win/dummy_platform.c | Stub Platform routines                                   |
| platforms/win/platform.h       | Platform specific declarations.                          |

The examples
------------

Three examples of the driver API are provided in the directory `driver/examples`.
`example_dma_ramp.c` shows how to generate ramps using DMA mode using the driver API.
In particular adi_dm_PeriodicCalibration is used to run calibrations between bursts.
`example_tasklist.c` also generates ramps using DMA but uses tasklists to run the
calibrations between bursts and to switch between burst profiles.
`example_syscal.c` shows how to perform 'end of line system calibration' to collect
t0 (time zero) measurements at the end of the systems production line. This data is
used in some built-in self-tests (BISTS).
Much of these examples are the same and have been broken out into common subroutines,
`example_init.c` contains the common initialization and `example_burst_loop.c` contains
the steady-state code for `example_dma_ramp.c`.

Platform specific code
----------------------

The driver API is only concerned with controlling ADAR690x devices. Other parts of the
application are concerned with controlling the host platform. These are represented by calls
in the example code to routines with names beginning `platform_`.

| Routine                        | Comment                                                   |
|--------------------------------|-----------------------------------------------------------|
| platform_init                  | Initialize drivers etc. on the host platform              |
| platform_data_plane_init       | Further initialization once device is initialized         |
| platform_error                 | Report an error and terminate program                     |
| platform_prep_host_for_trigger | Called before each trigger to prepare host for next burst |
| platform_start_timer           | Start a timer running in the background                   |
| platform_wait_for_timer        | Wait for the above timer or return immediately if expired |

The @ref HAL contains the platform specific code called by the driver itself.

Firmware in the examples
------------------------

The firmware must be loaded into the host platform memory before calling adi_dm_PowerUp().
The declaration of this memory region may depend upon how the platform code loads the
firmware so it has to appear in the file `platform.h` included by `application.h`.

The host is an embedded system so it may not be convenient to load the firmware at runtime.
The program `f2decl.c` which converts a binary file to C declarations is provided to support
this scenario. Nothing is assumed about the host system except it has a C compiler so the
program is distributed as C source code.

Example of `f2decl.c` use:

1. Compile and link f2decl.c to f2decl.exe
2. f2decl.exe adar690x_ICCMRAM.bin > adar690x_ICCMRAM.bin.c
3. f2decl.exe adar690x_DCCMRAM.bin > adar690x_DCCMRAM.bin.c

The example *VisualStudio* solution "examples\platforms\win\example.sln" performs these steps
automatically.
