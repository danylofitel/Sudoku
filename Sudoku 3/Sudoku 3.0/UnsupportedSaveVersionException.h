// Danylo Fitel 2026

#pragma once

namespace Sudoku_3_0
{
    // Thrown by SaveGameStore::Load when a file was written by a newer build than this one
    // understands. Carries the version numbers so the UI can show a specific message.
    public ref class UnsupportedSaveVersionException : public System::Exception
    {
    public:
        UnsupportedSaveVersionException(unsigned int fileVersion, unsigned int supportedVersion)
            : System::Exception(
                "Unsupported save format version " + fileVersion.ToString() +
                " (this build supports up to version " + supportedVersion.ToString() + ").")
        {
            this->FileVersion = fileVersion;
            this->SupportedVersion = supportedVersion;
        }

        // Format version found in the file.
        property unsigned int FileVersion;

        // Highest format version this build can load.
        property unsigned int SupportedVersion;
    };
}
