// Danylo Fitel 2026

#include "stdafx.h"
#include "BuildInfo.h" // generated at build time; defines SUDOKU_BUILD_STAMP and SUDOKU_FILE_VERSION

using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;

//
// General Information about an assembly is controlled through the following
// set of attributes. Change these attribute values to modify the information
// associated with an assembly.
//
[assembly:AssemblyTitleAttribute("Sudoku_3_0")];
[assembly:AssemblyDescriptionAttribute("")];
[assembly:AssemblyConfigurationAttribute("")];
[assembly:AssemblyCompanyAttribute("")];
[assembly:AssemblyProductAttribute("Sudoku_3_0")];
[assembly:AssemblyCopyrightAttribute("Copyright (c) 2013-2026 Danylo Fitel")];
[assembly:AssemblyTrademarkAttribute("")];
[assembly:AssemblyCultureAttribute("")];

//
// Version information for an assembly consists of the following four values:
//
//      Major Version
//      Minor Version
//      Build Number
//      Revision
//
// AssemblyVersion is the managed identity and is kept fixed so it does not change on every
// build. The per-build stamp lives in the file and informational versions below, generated in
// UTC by the GenerateBuildInfo MSBuild target:
//   AssemblyFileVersion        - numeric "File version" (1.0.<days since 2000>.<half-seconds>)
//   AssemblyInformationalVersion - human-readable UTC stamp, shown in About and "Product version"

[assembly:AssemblyVersionAttribute("1.0.0.0")];
[assembly:AssemblyFileVersionAttribute(SUDOKU_FILE_VERSION)];
[assembly:AssemblyInformationalVersionAttribute(SUDOKU_BUILD_STAMP)];

[assembly:ComVisible(false)];

[assembly:CLSCompliantAttribute(true)];
