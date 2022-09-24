#include "backend.h"
#include "crash_detection_umode.h"
#include "fshandle_table.h"
#include "fshooks.h"
#include "handle_table.h"
#include "targets.h"
#include <codecvt>
#include <fmt/format.h>

namespace fs = std::filesystem;

namespace nocap {

bool InsertTestcase(const uint8_t *Buffer, const size_t BufferSize) {
  g_FsHandleTable.MapExistingGuestFile(
      uR"(\??\C:\Users\snap\Desktop\mountains-clahe.jpg)", Buffer, BufferSize);
  // fmt::print("DONE! insert testcase\n");
  return true;
}


bool Init(const Options_t &Opts, const CpuState_t &CpuState) {

  if (!g_Backend->SetBreakpoint(Gva_t(0x004A2211), [](Backend_t *Backend) {
        Backend->Stop(Ok_t());
      })) {
    fmt::print("Failed to SetBreakpoint AfterCall\n");
    return false;
  }



  if (!g_Backend->SetBreakpoint(
          "USER32!SetWindowTextW", [](Backend_t *Backend) {
            Backend->SimulateReturnFrom32bitFunction(0, 2);
            // fmt::print("setwindows");
          })) {
    fmt::print("Failed to SetBreakpoint SetWindowsTextW\n");
    return false;
  }



  if (!g_Backend->SetBreakpoint("USER32!MessageBoxW", [](Backend_t *Backend) {
        Gva_t FormatPtr = Gva_t(Backend->Rsp());
        FormatPtr = FormatPtr + Gva_t(8);
        const uint32_t value = Backend->VirtRead4(FormatPtr);
        const std::u16string &Format = Backend->VirtReadWideString(Gva_t(value));

         fmt::print("msgBox----------------------------------------------------------\n");
         std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t>converter;
         std::cout << converter.to_bytes(Format) << std::endl;
         fmt::print("----------------------------------------------------------msgBox\n");

        Backend->SimulateReturnFrom32bitFunction(7, 4);
        //  fmt::print("msgBoxdaaed\n");
      })) {
    fmt::print("Failed to SetBreakpoint MessageBoxW\n");
    return false;
  }


  if (!g_Backend->SetBreakpoint(
          "KERNEL32!GetPrivateProfileIntW", [](Backend_t *Backend) {
            Gva_t FormatPtr = Gva_t(Backend->Rsp());
            FormatPtr = FormatPtr + Gva_t(0xc);
            const uint32_t value = Backend->VirtRead4(FormatPtr);
            // printf("%x", value);
            //  printf("\n");

            Backend->SimulateReturnFrom32bitFunction(value, 4);
            //   fmt::print("PrivateProfileInt\n");
          })) {
    fmt::print("Failed to SetBreakpoint GetPrivateProfileIntW\n");
    return false;
  }



  if (!g_Backend->SetBreakpoint(
          "KERNELBASE!LoadLibraryW", [](Backend_t *Backend) {
            Backend->SimulateReturnFrom32bitFunction(0, 1);
            // fmt::print("LOADLIBmyass\n");
          })) {
    fmt::print("Failed to SetBreakpoint LOADLIB\n");
    return false;
  }




  if (!SetupFilesystemHooks()) {
    fmt::print("Failed to SetupFilesystemHooks\n");
    return false;
  }

  // Instrument the Windows user-mode exception dispatcher to catch access
  // violations
  SetupUsermodeCrashDetectionHooks();

  g_HandleTable.Save();//important for fshooks
  return true;
}

bool Restore() {
  //
  // Restore the handle table and the fshooks.
  //

  g_HandleTable.Restore();
  return true;
}

// Register the target.
//

Target_t seriouslyy("seriouslyy", Init, InsertTestcase, Restore);

} // namespace seriouslyy
