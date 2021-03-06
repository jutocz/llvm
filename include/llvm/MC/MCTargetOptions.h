//===- MCTargetOptions.h - MC Target Options --------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_MC_MCTARGETOPTIONS_H
#define LLVM_MC_MCTARGETOPTIONS_H

#include <string>
#include <vector>

namespace llvm {

enum class ExceptionHandling {
  None,     /// No exception support
  DwarfCFI, /// DWARF-like instruction based exceptions
  SjLj,     /// setjmp/longjmp based exceptions
  ARM,      /// ARM EHABI
  WinEH,    /// Windows Exception Handling
};

class StringRef;

class MCTargetOptions {
public:
  enum AsmInstrumentation {
    AsmInstrumentationNone,
    AsmInstrumentationAddress
  };

  /// Enables AddressSanitizer instrumentation at machine level.
  bool SanitizeAddress : 1;

  bool MCRelaxAll : 1;
  bool MCNoExecStack : 1;
  bool MCFatalWarnings : 1;
  bool MCNoWarn : 1;
  bool MCNoDeprecatedWarn : 1;
  bool MCSaveTempLabels : 1;
  bool MCUseDwarfDirectory : 1;
  bool MCIncrementalLinkerCompatible : 1;
  bool MCPIECopyRelocations : 1;
  bool ShowMCEncoding : 1;
  bool ShowMCInst : 1;
  bool AsmVerbose : 1;

  /// Preserve Comments in Assembly.
  bool PreserveAsmComments : 1;

  int DwarfVersion = 0;

  std::string ABIName;

  /// Additional paths to search for `.include` directives when using the
  /// integrated assembler.
  std::vector<std::string> IASSearchPaths;

  MCTargetOptions();

  /// getABIName - If this returns a non-empty string this represents the
  /// textual name of the ABI that we want the backend to use, e.g. o32, or
  /// aapcs-linux.
  StringRef getABIName() const;
};

inline bool operator==(const MCTargetOptions &LHS, const MCTargetOptions &RHS) {
#define ARE_EQUAL(X) LHS.X == RHS.X
  return (ARE_EQUAL(SanitizeAddress) &&
          ARE_EQUAL(MCRelaxAll) &&
          ARE_EQUAL(MCNoExecStack) &&
          ARE_EQUAL(MCFatalWarnings) &&
          ARE_EQUAL(MCNoWarn) &&
          ARE_EQUAL(MCNoDeprecatedWarn) &&
          ARE_EQUAL(MCSaveTempLabels) &&
          ARE_EQUAL(MCUseDwarfDirectory) &&
          ARE_EQUAL(MCIncrementalLinkerCompatible) &&
          ARE_EQUAL(MCPIECopyRelocations) &&
          ARE_EQUAL(ShowMCEncoding) &&
          ARE_EQUAL(ShowMCInst) &&
          ARE_EQUAL(AsmVerbose) &&
          ARE_EQUAL(DwarfVersion) &&
          ARE_EQUAL(ABIName) &&
          ARE_EQUAL(IASSearchPaths));
#undef ARE_EQUAL
}

inline bool operator!=(const MCTargetOptions &LHS, const MCTargetOptions &RHS) {
  return !(LHS == RHS);
}

} // end namespace llvm

#endif // LLVM_MC_MCTARGETOPTIONS_H
