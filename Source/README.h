// Copyright 2012 Square Inc.
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

/*!
\mainpage
 
This client library reports exceptions to Squash, the Squarish exception
reporting and management system.

\section Documentation

Comprehensive documentation is written in YARD- and Markdown-formatted comments
throughout the source. To view this documentation as an HTML site, run Doxygen
with `doxygen Doxyfile`. Doxygen and Graphviz must be installed.

For an overview of the various components of Squash, see the website
documentation at https://github.com/SquareSquash/web.

\section Compatibility

This library is compatible with projects targeting iOS version 5.0 and above,
and written using Objective-C 2.0 or above.

\section Requirements

This library has no external third-party dependencies. It uses the
SystemConfiguration, CoreLocation, UIKit, and Foundation frameworks.

\section Usage

Compile the code with the correct scheme and architecture, creating a
libSquashCocoa.a library. Add this library to your project, being sure it is
included in your project's Link Binary With Libraries build phase. Add the
SquashCocoa.h header file to your project and import it:

\code{.m}
#import "SquashCocoa.h"
\endcode

Add the following code somewhere in your application that gets invoked on
startup, such as your app delegate's `application:didFinishLaunchingWithOptions:`
method:

\code{.m}
[SquashCocoa sharedClient].APIKey = @"YOUR_API_KEY";
[SquashCocoa sharedClient].environment = @"production";
[SquashCocoa sharedClient].host = @"https://your.squash.host";
[SquashCocoa sharedClient].revision = @"GIT_REVISION_OF_RELEASED_PRODUCT";
[[SquashCocoa sharedClient] reportErrors];
[[SquashCocoa sharedClient] hook];
\endcode

The SquashCocoa::reportErrors method loads any errors recorded from previous crashes and
transmits them to Squash. Errors are only removed from this queue when Squash
successfully receives them.

the SquashCocoa::hook method adds the uncaught-exception and default signal handlers that
allow Squash to record new crashes.

\section Configuration

You can configure the client using the properties of the
SquashCocoa::sharedClient singleton instance. The following properties are
available:

\subsection General

\li `disabled`: If `YES`, the Squash client will not report any errors.
\li `APIKey`: The API key of the project that exceptions will be associated with.
    This configuration option is required. The value can be found by going to the
    project's home page on Squash.
\li `environment`: The environment that exceptions will be associated with.
\li `revision`: The revision of the Git repository that was compiled to make this
    build. This field is required.

\subsection Error Transmission

\li `host`: The host on which Squash is running. This field is required.
\li `notifyPath`: The path to post new exception notifications to. By default it's
    set to `/api/1.0/notify`.
\li `notifyPath`: The path to post new exception notifications to. By default it's
    set to `/api/1.0/notify`.
\li `timeout`: The amount of time to wait before giving up on trasmitting an
    error. By default it's 15 seconds.

\subsection Exception Filtering

\li `ignoredExceptions`: A set of `NSException` names that will not be reported to
    Squash.
\li `handledSignals`: A set of signals (represented as `NSNumber`s) that Squash
    will trap. By default it's `SIGABRT`, `SIGBUS`, `SIGFPE`, `SIGILL`, `SIGSEGV`,
    and `SIGTRAP`.
\li `filterUserInfoKeys`: Keys to remove from the `userInfo` dictionary of any
    `NSException`. These keys might contain sensitive or personal information, for
    example.

\section Error Transmission

Exceptions are transmitted to Squash using JSON-over-HTTPS. A default API
endpoint is pre-configured, though you can always set your own (see
**Configuration** above).
*/
