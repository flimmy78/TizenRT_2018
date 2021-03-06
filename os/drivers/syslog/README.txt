drivers/syslog README File
==========================

This README file discusses the SYLOG drivers that can be found in the
drivers/syslog directory.  The syslogging interfaces are defined in the
header file include/syslog.h.  In TinyAra, "syslog output" is really
synonymous to "debug output" and, therefore, the debugging interfaces
defined in the header file include/debug.h are also sysloggin interfaces.

By default, all system log output goes to console (/dev/console).  But that
behavior can be changed by the defining CONFIG_SYSLOG in the TinyAra
configuration.  In that, case all low-level debug output will go through
syslog_putc().

One version of syslog_putc() is defined in fs/fs_syslog.c; that version is
used when CONFIG_SYSLOG_CHAR is defined.  That version of syslog_putc()
just integrates with the file system to re-direct debug output to a
character device or to a file. A disadvantage of using the generic character
device for the SYSLOG is that it cannot handle debug output generated from
interrupt level handles.

If CONFIG_SYSLOG_CHAR is not defined, then other custom SYSLOG drivers
can be used.  These custom SYSLOG drivers can do things like handle
unusual logging media and since they can avoid the general file system
interfaces, can be designed to support debug output from interrupt handlers.

Those custom SYSLOG drivers reside in this directory.

ramlog.c
--------
  The RAM logging driver is a driver that was intended to support debugging
  output (aka, syslogging).  It might be used when the normal serial output
  is not available.  For example, if you are using a Telnet or USB serial
  console, the debug output will get lost since the USB Telnet session does
  not use the serial console.

  The RAM logginc driver is also useful when debug output on the serial
  console would interfere with performance or with usability.  The debug
  output is write to RAM very quickly and so interferes less with realtime
  performance.  And since the output does not appear on the serial console
  until you want it to, it does not interfere with the usability of the
  serial console.  The TASH, for eample, supports a 'dmesg'
  command that can be used to dump the buffered output when you want to
  see it.

  The RAM logging  driver is similar to a pipe in that it saves the
  debugging output in a FIFO in RAM.  It differs from a pipe in numerous
  details as needed to support logging.

  This driver is built when CONFIG_RAMLOG is defined in the TinyAra
  configuration.

  Configuration options:

    CONFIG_RAMLOG - Enables the RAM logging feature
    CONFIG_RAMLOG_CONSOLE - Use the RAM logging device as a system console.
      If this feature is enabled (along with CONFIG_DEV_CONSOLE), then all
      console output will be re-directed to a circular buffer in RAM.  This
      is useful, for example, if the only console is a Telnet console.  Then
      in that case, console output from non-Telnet threads will go to the
      circular buffer and can be viewed using the TASH 'dmesg' command.
    CONFIG_RAMLOG_SYSLOG - Use the RAM logging device for the syslogging
      interface.  If this feature is enabled (along with CONFIG_SYSLOG),
      then all debug output (only) will be re-directed to the circular
      buffer in RAM.  This RAM log can be view from TASH using the 'dmesg'
      command.  NOTE:  Unlike the limited, generic character driver SYSLOG
      device, the RAMLOG *can* be used to generate debug output from interrupt
      level handlers.
    CONFIG_RAMLOG_NPOLLWAITERS - The number of threads than can be waiting
      for this driver on poll().  Default: 4

   If CONFIG_RAMLOG_CONSOLE or CONFIG_RAMLOG_SYSLOG is selected, then the
   following may also be provided:

   CONFIG_RAMLOG_BUFSIZE - Size of the console RAM log.  Default: 1024
