// Copyright 2012 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <err.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <string>
#include <system_error>

#include "llvm/IR/AssemblyAnnotationWriter.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/ToolOutputFile.h"
#include "regexp.h"

int main(int argc, char** argv) {
  const char* argv1 = argv[1];
  if (argv1 == nullptr) {
    errx(1, "regular expression not specified");
  }
  redgrep::Exp exp;
  if (!redgrep::Parse(argv1, &exp)) {
    errx(1, "parse error");
  }
  redgrep::DFA dfa;
  int nstates = redgrep::Compile(exp, &dfa);
  printf("; dfa is %d states\n", nstates);
  redgrep::Fun fun;
  redgrep::Compile(dfa, &fun);

  std::error_code EC;
  std::unique_ptr<llvm::ToolOutputFile> Out(
      new llvm::ToolOutputFile("-", EC, llvm::sys::fs::F_None));
  if (EC) {
    fprintf(stderr, "%s\n", EC.message().c_str());
    return 1;
  }

  std::unique_ptr<llvm::AssemblyAnnotationWriter> Annotator;

  fun.module_->print(Out->os(), Annotator.get());

  Out->keep();

  return 0;
}
