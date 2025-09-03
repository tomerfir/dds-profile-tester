# RTI Connext DDS XML Loader & Participant Validator

This project allows you to:
- Load and validate multiple RTI Connext DDS XML configuration files (XML Application Creation).

## Prerequisites

- RTI Connext DDS Professional 7.3.0 (or compatible version)
- RTI Connext DDS x64Win64VS2017 target libraries
- Visual Studio 2022 with x64 C++ v143 toolkit installed
- A valid RTI Connext DDS license

## Usage

```
./DDSProfileTester.exe <xml1.xml> <xml2.xml> ...
```
- Each argument should be a path to a valid RTI Connext DDS XML configuration file.

## Building

1. Clone this repository
2. Set up your RTI Connext DDS environment
3. Build with Visual Studio

# Attributions

## RTI Connext DDS Professional

This project uses RTI Connext DDS Professional, which is © 1996-2025 Real-Time Innovations, Inc. All rights reserved.

- RTI, Real-Time Innovations, Connext, Connext Drive, NDDS, the RTI logo, 1RTI, and the phrase “Your Systems. Working as one.” are registered trademarks, trademarks, or service marks of Real-Time Innovations, Inc.
- The software described in this project is furnished solely under and subject to RTI's standard terms and conditions available at [https://www.rti.com/terms](https://www.rti.com/terms) and in accordance with your License Acknowledgement Certificate (LAC) and Maintenance and Support Certificate (MSC), except to the extent otherwise agreed to in writing by RTI.
- RTI software may contain independent, third-party software or code that are subject to third-party license terms and conditions, including open source license terms and conditions. Copies of applicable third-party licenses and notices are located at [https://community.rti.com/documentation](https://community.rti.com/documentation). It is your responsibility to ensure that your use of third-party software complies with the corresponding third-party license terms and conditions.

For more information, see the [RTI Connext Professional Copyrights and Notices](https://community.rti.com/static/documentation/connext-dds/7.5.0/doc/manuals/connext_dds_professional/installation_guide/copyright.html).

## tinyxml2

This project uses [tinyxml2](https://github.com/leethomason/tinyxml2), which is Copyright (c) 2000-2024 Lee Thomason (www.grinninglizard.com)

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
This notice may not be removed or altered from any source distribution.

**It is your responsibility to ensure that your use of RTI Connext DDS and tinyxml2 complies with their respective license terms and conditions.**