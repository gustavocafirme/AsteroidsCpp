#include "Sounds.h"
#include "resource.h"
#include <Windows.h>
#include <thread>
#include <cstring>

#pragma comment(lib, "winmm.lib")

namespace
{
	// Stores the information from the WAV file to memory
	struct WavData
	{
		WAVEFORMATEX format;
		const char* pSamples;
		DWORD samplesSize;
		bool isValid;
	};

	// Analyses the struct from the RIFF/WAV container from RAM
	// Locates the "fmt" and "data" chunks dynamically, ignoring extra metadata (LIST, INFO, etc.)
	WavData parseWavMemory(const char* data, DWORD size)
	{
		WavData result = {};
		if (!data || size < 12) return result;

		// Validates if the header is a RIFF file of the WAVE type
		if (std::memcmp(data, "RIFF", 4) != 0 || std::memcmp(data + 8, "WAVE", 4) != 0) {
			return result;
		}

		DWORD offset = 12;
		bool foundFmt = false;
		bool foundData = false;

		while (offset + 8 <= size) {
			const char* chunkId = data + offset;
			DWORD chunkSize = *reinterpret_cast<const DWORD*>(data + offset + 4);

			if (offset + 8 + chunkSize > size) break;

			// Chunk formatted as ("fmt ")
			if (std::memcmp(chunkId, "fmt ", 4) == 0 && chunkSize >= 16) {
				std::memset(&result.format, 0, sizeof(WAVEFORMATEX));
				std::memcpy(&result.format, data + offset + 8, (chunkSize < 16) ? chunkSize : 16);
				result.format.cbSize = 0;
				foundFmt = true;
			}
			// Data chunk from Audio ("data")
			else if (std::memcmp(chunkId, "data", 4) == 0) {
				result.pSamples = data + offset + 8;
				result.samplesSize = chunkSize;
				foundData = true;
			}

			if (foundFmt && foundData) {
				result.isValid = true;
				break;
			}

			// WAV chunks are aligned in pairs of bytes (word-alignment)
			DWORD paddedSize = chunkSize + (chunkSize % 2);
			offset += 8 + paddedSize;
		}

		return result;
	}

	// Plays the resource directly from memory in an independent audio channel
	void playResourceWaveOut(UINT resourceId)
	{
		std::thread([resourceId]() {
			HMODULE hModule = GetModuleHandle(NULL);
			HRSRC hRes = FindResource(hModule, MAKEINTRESOURCE(resourceId), TEXT("WAVE"));
			if (!hRes) return;

			HGLOBAL hMem = LoadResource(hModule, hRes);
			if (!hMem) return;

			DWORD soundSize = SizeofResource(hModule, hRes);
			const char* soundData = static_cast<const char*>(LockResource(hMem));
			if (!soundData || soundSize == 0) return;

			// Dynamic parse of the audio struct
			WavData wav = parseWavMemory(soundData, soundSize);
			if (!wav.isValid) return;

			HWAVEOUT hWaveOut = NULL;
			if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wav.format, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
				return;
			}

			WAVEHDR waveHeader = {};
			waveHeader.lpData = const_cast<char*>(wav.pSamples);
			waveHeader.dwBufferLength = wav.samplesSize;

			if (waveOutPrepareHeader(hWaveOut, &waveHeader, sizeof(WAVEHDR)) == MMSYSERR_NOERROR) {
				waveOutWrite(hWaveOut, &waveHeader, sizeof(WAVEHDR));

				// Awaits for playback to finish on the asynchronous channel
				while (!(waveHeader.dwFlags & WHDR_DONE)) {
					Sleep(5);
				}

				waveOutUnprepareHeader(hWaveOut, &waveHeader, sizeof(WAVEHDR));
			}

			waveOutClose(hWaveOut);
			}).detach();
	}
}

namespace Sounds
{
	void playMenuSelectSound() {
		playResourceWaveOut(IDR_WAVE_MENUSELECT);
	}
	void playMenuHitSound() {
		playResourceWaveOut(IDR_WAVE_MENUHIT);
	}
	void playMenuBackSound() {
		playResourceWaveOut(IDR_WAVE_MENUBACK);
	}
	void playMenuExitSound() {
		playResourceWaveOut(IDR_WAVE_MENUBACK);
	}

	void playGunSound() {
		playResourceWaveOut(IDR_WAVE_LASERGUN01);
	}
	void playShipExplosionSound() {
		playResourceWaveOut(IDR_WAVE_EXPLOSION01);
	}
	void playAsteroidExplosionSound() {
		playResourceWaveOut(IDR_WAVE_EXPLOSION01);
	}

	void playPauseSound() {
		playResourceWaveOut(IDR_WAVE_MENUSELECT);
	}
	void playHelpSound() {
		playResourceWaveOut(IDR_WAVE_HELPHIT);
	}

	void playStageCompletedSound() {
		playResourceWaveOut(IDR_WAVE_SUCCESS);
	}
	void playGameOverSound() {
		playResourceWaveOut(IDR_WAVE_FAILURE);
	}
}