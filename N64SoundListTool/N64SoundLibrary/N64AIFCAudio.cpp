	#pragma once

#include "StdAfx.h"
#include "N64AIFCAudio.h"
#include <math.h>
#include "..\N64SoundLibrary\flzh_rn.h"
float CN64AIFCAudio::keyTable[0xFF];

CN64AIFCAudio::CN64AIFCAudio(void)
{
	InitializeKeyTable();
}

CN64AIFCAudio::~CN64AIFCAudio(void)
{
}

CString CN64AIFCAudio::CompareALInstrument(ALInst* alInst1, ALInst* alInst2)
{
	CString errors = "";

	if (alInst1->volume != alInst2->volume)
		errors += "Differing instr volume counts\r\n";
	if (alInst1->pan != alInst2->pan)
		errors += "Differing instr pan counts\r\n";
	if (alInst1->priority != alInst2->priority)
		errors += "Differing instr priority counts\r\n";
	if (alInst1->flags != alInst2->flags)
		errors += "Differing instr flags counts\r\n";
	if (alInst1->tremType != alInst2->tremType)
		errors += "Differing instr tremType counts\r\n";
	if (alInst1->tremRate != alInst2->tremRate)
		errors += "Differing instr tremRate counts\r\n";
	if (alInst1->tremDepth != alInst2->tremDepth)
		errors += "Differing instr tremDepth counts\r\n";
	if (alInst1->tremDelay != alInst2->tremDelay)
		errors += "Differing instr tremDelay counts\r\n";
	if (alInst1->vibType != alInst2->vibType)
		errors += "Differing instr vibType counts\r\n";
	if (alInst1->vibRate != alInst2->vibRate)
		errors += "Differing instr vibRate counts\r\n";
	if (alInst1->vibDelay != alInst2->vibDelay)
		errors += "Differing instr vibDelay counts\r\n";
	if (alInst1->bendRange != alInst2->bendRange)
		errors += "Differing instr bendRange counts\r\n";
	if (alInst1->soundCount != alInst2->soundCount)
	{
		errors += "Differing instr soundCount counts\r\n";
		return errors;
	}

	for (int y = 0; y < alInst1->soundCount; y++)
	{
		if (alInst1->sounds[y]->samplePan != alInst2->sounds[y]->samplePan)
			errors += "Differing instr samplePan counts\r\n";
		if (alInst1->sounds[y]->sampleVolume != alInst2->sounds[y]->sampleVolume)
			errors += "Differing instr sampleVolume counts\r\n";
		if (alInst1->sounds[y]->flags != alInst2->sounds[y]->flags)
			errors += "Differing instr flags counts\r\n";

		if (alInst1->sounds[y]->env.attackTime != alInst2->sounds[y]->env.attackTime)
			errors += "Differing sound attackTime counts\r\n";
		if (alInst1->sounds[y]->env.decayTime != alInst2->sounds[y]->env.decayTime)
			errors += "Differing sound decayTime counts\r\n";
		if (alInst1->sounds[y]->env.releaseTime != alInst2->sounds[y]->env.releaseTime)
			errors += "Differing sound releaseTime counts\r\n";
		if (alInst1->sounds[y]->env.attackVolume != alInst2->sounds[y]->env.attackVolume)
			errors += "Differing sound attackVolume counts\r\n";
		if (alInst1->sounds[y]->env.decayVolume != alInst2->sounds[y]->env.decayVolume)
			errors += "Differing sound decayVolume counts\r\n";

		if (alInst1->sounds[y]->key.velocitymin != alInst2->sounds[y]->key.velocitymin)
			errors += "Differing sound velocitymin counts\r\n";
		if (alInst1->sounds[y]->key.velocitymax != alInst2->sounds[y]->key.velocitymax)
			errors += "Differing sound velocitymax counts\r\n";
		if (alInst1->sounds[y]->key.keymin != alInst2->sounds[y]->key.keymin)
			errors += "Differing sound keymin counts\r\n";
		if (alInst1->sounds[y]->key.keymax != alInst2->sounds[y]->key.keymax)
			errors += "Differing sound keymax counts\r\n";
		if (alInst1->sounds[y]->key.keybase != alInst2->sounds[y]->key.keybase)
			errors += "Differing sound keybase counts\r\n";
		if (alInst1->sounds[y]->key.detune != alInst2->sounds[y]->key.detune)
			errors += "Differing sound detune counts\r\n";

		if (alInst1->sounds[y]->wav.len != alInst2->sounds[y]->wav.len)
			errors += "Differing sound len\r\n";
		if (alInst1->sounds[y]->wav.type != alInst2->sounds[y]->wav.type)
			errors += "Differing sound len\r\n";
		if (alInst1->sounds[y]->wav.flags != alInst2->sounds[y]->wav.flags)
			errors += "Differing sound flags\r\n";

		if ((alInst1->sounds[y]->wav.type == 0) && (alInst2->sounds[y]->wav.type == 0))
		{
			if ((alInst1->sounds[y]->wav.adpcmWave->loop != NULL) && (alInst2->sounds[y]->wav.adpcmWave->loop != NULL))
			{
				if (alInst1->sounds[y]->wav.adpcmWave->loop->start != alInst2->sounds[y]->wav.adpcmWave->loop->start)
					errors += "Differing loop start flags\r\n";
				if (alInst1->sounds[y]->wav.adpcmWave->loop->end != alInst2->sounds[y]->wav.adpcmWave->loop->end)
					errors += "Differing loop end flags\r\n";
				if (alInst1->sounds[y]->wav.adpcmWave->loop->count != alInst2->sounds[y]->wav.adpcmWave->loop->count)
					errors += "Differing loop count flags\r\n";

				for (int z = 0; z < 0x10; z++)
				{
					if (alInst1->sounds[y]->wav.adpcmWave->loop->state[z] != alInst2->sounds[y]->wav.adpcmWave->loop->state[z])
						errors += "Differing loop state flags\r\n";
				}
			}
			else if (((alInst1->sounds[y]->wav.adpcmWave->loop != NULL) && (alInst2->sounds[y]->wav.adpcmWave->loop == NULL)) || 
				((alInst1->sounds[y]->wav.adpcmWave->loop == NULL) && (alInst2->sounds[y]->wav.adpcmWave->loop != NULL)))
			{
				errors += "Differing loop null\r\n";
			}

			if (alInst1->sounds[y]->wav.adpcmWave->book->order != alInst2->sounds[y]->wav.adpcmWave->book->order)
			{
					errors += "Differing book->order\r\n";
					continue;
			}
			if (alInst1->sounds[y]->wav.adpcmWave->book->npredictors != alInst2->sounds[y]->wav.adpcmWave->book->npredictors)
			{
					errors += "Differing book->npredictors\r\n";
					continue;
			}

			for (int z = 0; z < (alInst1->sounds[y]->wav.adpcmWave->book->order * alInst1->sounds[y]->wav.adpcmWave->book->npredictors * 8); z++)
			{
				if (alInst1->sounds[y]->wav.adpcmWave->book->predictors[z] != alInst2->sounds[y]->wav.adpcmWave->book->predictors[z])
					errors += "Differing predictors \r\n";
			}
		}
		else if ((alInst1->sounds[y]->wav.type == 1) && (alInst2->sounds[y]->wav.type == 1))
		{
			if ((alInst1->sounds[y]->wav.rawWave->loop != NULL) && (alInst2->sounds[y]->wav.rawWave->loop != NULL))
			{
				if (alInst1->sounds[y]->wav.rawWave->loop->start != alInst2->sounds[y]->wav.rawWave->loop->start)
					errors += "Differing loop start flags\r\n";
				if (alInst1->sounds[y]->wav.rawWave->loop->end != alInst2->sounds[y]->wav.rawWave->loop->end)
					errors += "Differing loop end flags\r\n";
				if (alInst1->sounds[y]->wav.rawWave->loop->count != alInst2->sounds[y]->wav.rawWave->loop->count)
					errors += "Differing loop count flags\r\n";
			}
			else if (((alInst1->sounds[y]->wav.rawWave->loop != NULL) && (alInst2->sounds[y]->wav.rawWave->loop == NULL)) || 
				((alInst1->sounds[y]->wav.rawWave->loop == NULL) && (alInst2->sounds[y]->wav.rawWave->loop != NULL)))
			{
				errors += "Differing loop null flags\r\n";
			}
		}

		if (alInst1->sounds[y]->wav.len == alInst2->sounds[y]->wav.len)
		{
			for (int z = 0; z < alInst1->sounds[y]->wav.len; z++)
			{
				if (alInst1->sounds[y]->wav.wavData[z] != alInst2->sounds[y]->wav.wavData[z])
				{
					errors += "tbl mismatch\r\n";
					break;
				}
			}
		}
	}

	return errors;
}

CString CN64AIFCAudio::CompareALBanks(ALBank* alBank1, ALBank* alBank2)
{
	CString errors = "";
	if (alBank1->count != alBank2->count)
		errors += "Differing instr counts\r\n";
	if (alBank1->flags != alBank2->flags)
		errors += "Differing bank flags counts\r\n";
	if (alBank1->samplerate != alBank2->samplerate)
		errors += "Differing bank samplerate counts\r\n";

	if ((alBank1->percussion == NULL) && (alBank2->percussion != NULL))
		errors += "Differing percussion +1 -2";
	else if ((alBank1->percussion != NULL) && (alBank2->percussion == NULL))
		errors += "Differing percussion -1 +2";
	else if ((alBank1->percussion != NULL) && (alBank2->percussion != NULL))
		errors += CompareALInstrument(alBank1->percussion, alBank2->percussion);

	for (int x = 0; x < alBank1->count; x++)
	{
		errors += CompareALInstrument(alBank1->inst[x], alBank2->inst[x]);
	}

	return errors;
}

bool CN64AIFCAudio::ExtractEADPercussionRawPCMData(CString mainFolder, ALBank* alBank, int sound, CString outputFile)
{
	if (alBank->countEADPercussion > 0)
	{
		if (alBank->eadPercussion[sound].wav.type == AL_RAW16_WAVE)
		{
			FILE* outFileTempRaw = fopen(outputFile, "wb");
			if (outFileTempRaw == NULL)
			{
				MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
				return false;
			}

			fwrite(&alBank->eadPercussion[sound].wav.wavData[1], 1, (alBank->eadPercussion[sound].wav.len-2), outFileTempRaw);
			fclose(outFileTempRaw);

			return true;
		}
		else
		{
			// hack for mario kart
			if ((alBank->eadPercussion[sound].wav.adpcmWave == NULL) || (alBank->eadPercussion[sound].wav.adpcmWave->book == NULL))
				return false;

			signed short* outRawData = new signed short[alBank->eadPercussion[sound].wav.len * 4];
			int nSamples = decode(alBank->eadPercussion[sound].wav.wavData, outRawData, alBank->eadPercussion[sound].wav.len, alBank->eadPercussion[sound].wav.adpcmWave->book, alBank->eadPercussion[sound].wav.decode8Only);
			
			FILE* outFileTempRaw = fopen(outputFile, "wb");
			if (outFileTempRaw == NULL)
			{
				MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
				return false;
			}

			for (int x = 0; x < nSamples; x++)
			{
				fwrite(&outRawData[x], 1,2, outFileTempRaw);
			}

			fclose(outFileTempRaw);

			delete [] outRawData;
			return true;
		}
	}
	return false;
}

bool CN64AIFCAudio::ExtractSfxRawPCMData(CString mainFolder, ALBank* alBank, int sound, CString outputFile)
{
	if (alBank->countSfx > 0)
	{
		if (alBank->alSfx[sound]->type == AL_RAW16_WAVE)
		{
			FILE* outFileTempRaw = fopen(outputFile, "wb");
			if (outFileTempRaw == NULL)
			{
				MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
				return false;
			}

			fwrite(&alBank->alSfx[sound]->wavData[1], 1, (alBank->alSfx[sound]->len-2), outFileTempRaw);
			fclose(outFileTempRaw);

			return true;
		}
		else
		{
			// hack for mario kart
			if ((alBank->alSfx[sound]->adpcmWave == NULL) || (alBank->alSfx[sound]->adpcmWave->book == NULL))
				return false;

			signed short* outRawData = new signed short[alBank->alSfx[sound]->len * 4];
			int nSamples = decode(alBank->alSfx[sound]->wavData, outRawData, alBank->alSfx[sound]->len, alBank->alSfx[sound]->adpcmWave->book, alBank->alSfx[sound]->decode8Only);
			
			FILE* outFileTempRaw = fopen(outputFile, "wb");
			if (outFileTempRaw == NULL)
			{
				MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
				return false;
			}

			for (int x = 0; x < nSamples; x++)
			{
				fwrite(&outRawData[x], 1,2, outFileTempRaw);
			}

			fclose(outFileTempRaw);

			delete [] outRawData;
			return true;
		}
	}
	return false;
}

bool CN64AIFCAudio::ExtractEADPercussion(ALBank* alBank, int sound, CString outputFile, unsigned long samplingRate, bool ignoreKeyBase, bool halfSamplingRate)
{
	if (alBank->countEADPercussion > 0)
	{
		float samplingRateFloat = (float)samplingRate;

		/*if (!ignoreKeyBase)
		{
			if (
						(alBank->soundBankFormat == SUPERMARIO64FORMAT)
						|| (alBank->soundBankFormat == MARIOKART64FORMAT) 
						|| (alBank->soundBankFormat == ZELDAFORMAT)
						|| (alBank->soundBankFormat == STARFOX64FORMAT)
						|| (alBank->soundBankFormat == FZEROFORMAT)
					)
			{
				samplingRateFloat = samplingRateFloat / (*reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->unknown3 == 0) ? 1 : *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->unknown3);
			}
		}*/

		if (halfSamplingRate)
		{
			samplingRateFloat = samplingRateFloat / 2;
		}


		if (alBank->eadPercussion[sound].wav.type == AL_RAW16_WAVE)
		{
			FILE* outFileTempRaw = fopen(outputFile, "wb");
			if (outFileTempRaw == NULL)
			{
				MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
				return false;
			}

			unsigned char* wavHeader = new unsigned char[0x28];


			wavHeader[0x0] = 0x52;
			wavHeader[0x1] = 0x49;
			wavHeader[0x2] = 0x46;
			wavHeader[0x3] = 0x46;
			unsigned long chunkSize = 0x28 + (alBank->eadPercussion[sound].wav.len-2) + 0x44 - 0x8;
			wavHeader[0x4] = ((chunkSize >> 0) & 0xFF);
			wavHeader[0x5] = ((chunkSize >> 8) & 0xFF);
			wavHeader[0x6] = ((chunkSize >> 16) & 0xFF);
			wavHeader[0x7] = ((chunkSize >> 24) & 0xFF);
			wavHeader[0x8] = 0x57;
			wavHeader[0x9] = 0x41;
			wavHeader[0xA] = 0x56;
			wavHeader[0xB] = 0x45;
			wavHeader[0xC] = 0x66;
			wavHeader[0xD] = 0x6D;
			wavHeader[0xE] = 0x74;
			wavHeader[0xF] = 0x20;
			wavHeader[0x10] = 0x10;
			wavHeader[0x11] = 0x00;
			wavHeader[0x12] = 0x00;
			wavHeader[0x13] = 0x00;
			wavHeader[0x14] = 0x01;
			wavHeader[0x15] = 0x00;
			wavHeader[0x16] = 0x01;
			wavHeader[0x17] = 0x00;
			wavHeader[0x18] = (((unsigned long)samplingRateFloat >> 0) & 0xFF);
			wavHeader[0x19] = (((unsigned long)samplingRateFloat >> 8) & 0xFF);
			wavHeader[0x1A] = (((unsigned long)samplingRateFloat >> 16) & 0xFF);
			wavHeader[0x1B] = (((unsigned long)samplingRateFloat >> 24) & 0xFF);
			wavHeader[0x1C] = ((((unsigned long)samplingRateFloat * 2) >> 0) & 0xFF);
			wavHeader[0x1D] = ((((unsigned long)samplingRateFloat * 2) >> 8) & 0xFF);
			wavHeader[0x1E] = ((((unsigned long)samplingRateFloat * 2) >> 16) & 0xFF);
			wavHeader[0x1F] = ((((unsigned long)samplingRateFloat * 2) >> 24) & 0xFF);
			wavHeader[0x20] = 0x02;
			wavHeader[0x21] = 0x00;
			wavHeader[0x22] = 0x10;
			wavHeader[0x23] = 0x00;
			wavHeader[0x24] = 0x64;
			wavHeader[0x25] = 0x61;
			wavHeader[0x26] = 0x74;
			wavHeader[0x27] = 0x61;

			fwrite(wavHeader, 1, 0x28, outFileTempRaw );

			delete [] wavHeader;

			unsigned long length = (alBank->eadPercussion[sound].wav.len-2);
			fwrite(&length, 1, 4, outFileTempRaw);

			fwrite(&alBank->eadPercussion[sound].wav.wavData[1], 1, (alBank->eadPercussion[sound].wav.len-2), outFileTempRaw);

			
			if (alBank->eadPercussion[sound].wav.rawWave->loop != NULL)
			{
				unsigned char* wavHeader = new unsigned char[0x44];
				for (int x = 0; x < 0x44; x++)
					wavHeader[x] = 0x00;

				wavHeader[0x0] = 0x73;
				wavHeader[0x1] = 0x6D;
				wavHeader[0x2] = 0x70;
				wavHeader[0x3] = 0x6C;
				wavHeader[0x4] = 0x3C;
				wavHeader[0x5] = 0x00;
				wavHeader[0x6] = 0x00;
				wavHeader[0x7] = 0x00;
				
				if (
						(alBank->soundBankFormat == SUPERMARIO64FORMAT)
						|| (alBank->soundBankFormat == MARIOKART64FORMAT) 
						|| (alBank->soundBankFormat == ZELDAFORMAT)
						|| (alBank->soundBankFormat == STARFOX64FORMAT)
						|| (alBank->soundBankFormat == FZEROFORMAT)
					)
				{
					float keybaseFloat = *reinterpret_cast<float*> (&alBank->eadPercussion[sound].keyBase);
					wavHeader[0x14] = ConvertEADGameValueToKeyBase(keybaseFloat);
				}
				else
					wavHeader[0x14] = 0x3C;
				wavHeader[0x15] = 0x00;
				wavHeader[0x16] = 0x00;
				wavHeader[0x17] = 0x00;
				
				wavHeader[0x24] = 0x01;
				wavHeader[0x25] = 0x00;
				wavHeader[0x26] = 0x00;
				wavHeader[0x27] = 0x00;

				if (alBank->eadPercussion[sound].wav.rawWave->loop->count > 0)
				{
					wavHeader[0x34] = ((alBank->eadPercussion[sound].wav.rawWave->loop->start >> 0) & 0xFF);
					wavHeader[0x35] = ((alBank->eadPercussion[sound].wav.rawWave->loop->start >> 8) & 0xFF);
					wavHeader[0x36] = ((alBank->eadPercussion[sound].wav.rawWave->loop->start >> 16) & 0xFF);
					wavHeader[0x37] = ((alBank->eadPercussion[sound].wav.rawWave->loop->start >> 24) & 0xFF);
					wavHeader[0x38] = (((alBank->eadPercussion[sound].wav.rawWave->loop->end) >> 0) & 0xFF);
					wavHeader[0x39] = (((alBank->eadPercussion[sound].wav.rawWave->loop->end) >> 8) & 0xFF);
					wavHeader[0x3A] = (((alBank->eadPercussion[sound].wav.rawWave->loop->end) >> 16) & 0xFF);
					wavHeader[0x3B] = (((alBank->eadPercussion[sound].wav.rawWave->loop->end) >> 24) & 0xFF);

					if (alBank->eadPercussion[sound].wav.rawWave->loop->count == 0xFFFFFFFF)
					{
						wavHeader[0x40] = 0x00;
						wavHeader[0x41] = 0x00;
						wavHeader[0x42] = 0x00;
						wavHeader[0x43] = 0x00;
					}
					else
					{
						wavHeader[0x40] = (((alBank->eadPercussion[sound].wav.rawWave->loop->count) >> 0) & 0xFF);
						wavHeader[0x41] = (((alBank->eadPercussion[sound].wav.rawWave->loop->count) >> 8) & 0xFF);
						wavHeader[0x42] = (((alBank->eadPercussion[sound].wav.rawWave->loop->count) >> 16) & 0xFF);
						wavHeader[0x43] = (((alBank->eadPercussion[sound].wav.rawWave->loop->count) >> 24) & 0xFF);
					}
				}

				fwrite(wavHeader, 1, 0x44, outFileTempRaw );

				delete [] wavHeader;
			}
			else
			{
				unsigned char* wavHeader = new unsigned char[0x44];
				for (int x = 0; x < 0x44; x++)
					wavHeader[x] = 0x00;

				wavHeader[0x0] = 0x73;
				wavHeader[0x1] = 0x6D;
				wavHeader[0x2] = 0x70;
				wavHeader[0x3] = 0x6C;
				wavHeader[0x4] = 0x3C;
				wavHeader[0x5] = 0x00;
				wavHeader[0x6] = 0x00;
				wavHeader[0x7] = 0x00;
				
				if (
						(alBank->soundBankFormat == SUPERMARIO64FORMAT)
						|| (alBank->soundBankFormat == MARIOKART64FORMAT) 
						|| (alBank->soundBankFormat == ZELDAFORMAT)
						|| (alBank->soundBankFormat == STARFOX64FORMAT)
						|| (alBank->soundBankFormat == FZEROFORMAT)
					)
				{
					float keybaseFloat = *reinterpret_cast<float*> (&alBank->eadPercussion[sound].keyBase);
					wavHeader[0x14] = ConvertEADGameValueToKeyBase(keybaseFloat);
				}
				else
					wavHeader[0x14] = 0x3C;
				wavHeader[0x15] = 0x00;
				wavHeader[0x16] = 0x00;
				wavHeader[0x17] = 0x00;

				fwrite(wavHeader, 1, 0x44, outFileTempRaw );

				delete [] wavHeader;
			}


			fclose(outFileTempRaw);

			return true;
		}
		else
		{
			// hack for mario kart
			if ((alBank->eadPercussion[sound].wav.adpcmWave == NULL) || (alBank->eadPercussion[sound].wav.adpcmWave->book == NULL))
				return false;

			signed short* outRawData = new signed short[alBank->eadPercussion[sound].wav.len * 4];
			int nSamples = decode(alBank->eadPercussion[sound].wav.wavData, outRawData, alBank->eadPercussion[sound].wav.len, alBank->eadPercussion[sound].wav.adpcmWave->book, alBank->eadPercussion[sound].wav.decode8Only);
			
			FILE* outFileTempRaw = fopen(outputFile, "wb");
			if (outFileTempRaw == NULL)
			{
				MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
				return false;
			}

			unsigned char* wavHeader = new unsigned char[0x28];


			wavHeader[0x0] = 0x52;
			wavHeader[0x1] = 0x49;
			wavHeader[0x2] = 0x46;
			wavHeader[0x3] = 0x46;
			unsigned long chunkSize = 0x28 + (nSamples * 2) + 0x44 - 0x8;
			wavHeader[0x4] = ((chunkSize >> 0) & 0xFF);
			wavHeader[0x5] = ((chunkSize >> 8) & 0xFF);
			wavHeader[0x6] = ((chunkSize >> 16) & 0xFF);
			wavHeader[0x7] = ((chunkSize >> 24) & 0xFF);
			wavHeader[0x8] = 0x57;
			wavHeader[0x9] = 0x41;
			wavHeader[0xA] = 0x56;
			wavHeader[0xB] = 0x45;
			wavHeader[0xC] = 0x66;
			wavHeader[0xD] = 0x6D;
			wavHeader[0xE] = 0x74;
			wavHeader[0xF] = 0x20;
			wavHeader[0x10] = 0x10;
			wavHeader[0x11] = 0x00;
			wavHeader[0x12] = 0x00;
			wavHeader[0x13] = 0x00;
			wavHeader[0x14] = 0x01;
			wavHeader[0x15] = 0x00;
			wavHeader[0x16] = 0x01;
			wavHeader[0x17] = 0x00;
			wavHeader[0x18] = ((samplingRate >> 0) & 0xFF);
			wavHeader[0x19] = ((samplingRate >> 8) & 0xFF);
			wavHeader[0x1A] = ((samplingRate >> 16) & 0xFF);
			wavHeader[0x1B] = ((samplingRate >> 24) & 0xFF);
			wavHeader[0x1C] = ((((unsigned long)samplingRateFloat * 2) >> 0) & 0xFF);
			wavHeader[0x1D] = ((((unsigned long)samplingRateFloat * 2) >> 8) & 0xFF);
			wavHeader[0x1E] = ((((unsigned long)samplingRateFloat * 2) >> 16) & 0xFF);
			wavHeader[0x1F] = ((((unsigned long)samplingRateFloat * 2) >> 24) & 0xFF);
			wavHeader[0x20] = 0x02;
			wavHeader[0x21] = 0x00;
			wavHeader[0x22] = 0x10;
			wavHeader[0x23] = 0x00;
			wavHeader[0x24] = 0x64;
			wavHeader[0x25] = 0x61;
			wavHeader[0x26] = 0x74;
			wavHeader[0x27] = 0x61;

			fwrite(wavHeader, 1, 0x28, outFileTempRaw );

			delete [] wavHeader;

			unsigned long length = (nSamples * 2);
			fwrite(&length, 1, 4, outFileTempRaw);

			for (int x = 0; x < nSamples; x++)
			{
				fwrite(&outRawData[x], 1,2, outFileTempRaw);
			}

			if (alBank->eadPercussion[sound].wav.adpcmWave->loop != NULL)
			{
				unsigned char* wavHeader = new unsigned char[0x44];
				for (int x = 0; x < 0x44; x++)
					wavHeader[x] = 0x00;

				wavHeader[0x0] = 0x73;
				wavHeader[0x1] = 0x6D;
				wavHeader[0x2] = 0x70;
				wavHeader[0x3] = 0x6C;
				wavHeader[0x4] = 0x3C;
				wavHeader[0x5] = 0x00;
				wavHeader[0x6] = 0x00;
				wavHeader[0x7] = 0x00;
				
				if (
						(alBank->soundBankFormat == SUPERMARIO64FORMAT)
						|| (alBank->soundBankFormat == MARIOKART64FORMAT) 
						|| (alBank->soundBankFormat == ZELDAFORMAT)
						|| (alBank->soundBankFormat == STARFOX64FORMAT)
						|| (alBank->soundBankFormat == FZEROFORMAT)
					)
				{
					float keybaseFloat = *reinterpret_cast<float*> (&alBank->eadPercussion[sound].keyBase);
					wavHeader[0x14] = ConvertEADGameValueToKeyBase(keybaseFloat);
				}
				else
					wavHeader[0x14] = 0x3C;
				wavHeader[0x15] = 0x00;
				wavHeader[0x16] = 0x00;
				wavHeader[0x17] = 0x00;
				
				wavHeader[0x24] = 0x01;
				wavHeader[0x25] = 0x00;
				wavHeader[0x26] = 0x00;
				wavHeader[0x27] = 0x00;

				if (alBank->eadPercussion[sound].wav.adpcmWave->loop->count > 0)
				{
					wavHeader[0x34] = ((alBank->eadPercussion[sound].wav.adpcmWave->loop->start >> 0) & 0xFF);
					wavHeader[0x35] = ((alBank->eadPercussion[sound].wav.adpcmWave->loop->start >> 8) & 0xFF);
					wavHeader[0x36] = ((alBank->eadPercussion[sound].wav.adpcmWave->loop->start >> 16) & 0xFF);
					wavHeader[0x37] = ((alBank->eadPercussion[sound].wav.adpcmWave->loop->start >> 24) & 0xFF);
					wavHeader[0x38] = (((alBank->eadPercussion[sound].wav.adpcmWave->loop->end) >> 0) & 0xFF);
					wavHeader[0x39] = (((alBank->eadPercussion[sound].wav.adpcmWave->loop->end) >> 8) & 0xFF);
					wavHeader[0x3A] = (((alBank->eadPercussion[sound].wav.adpcmWave->loop->end) >> 16) & 0xFF);
					wavHeader[0x3B] = (((alBank->eadPercussion[sound].wav.adpcmWave->loop->end) >> 24) & 0xFF);

					if (alBank->eadPercussion[sound].wav.adpcmWave->loop->count == 0xFFFFFFFF)
					{
						wavHeader[0x40] = 0x00;
						wavHeader[0x41] = 0x00;
						wavHeader[0x42] = 0x00;
						wavHeader[0x43] = 0x00;
					}
					else
					{
						wavHeader[0x40] = (((alBank->eadPercussion[sound].wav.adpcmWave->loop->count) >> 0) & 0xFF);
						wavHeader[0x41] = (((alBank->eadPercussion[sound].wav.adpcmWave->loop->count) >> 8) & 0xFF);
						wavHeader[0x42] = (((alBank->eadPercussion[sound].wav.adpcmWave->loop->count) >> 16) & 0xFF);
						wavHeader[0x43] = (((alBank->eadPercussion[sound].wav.adpcmWave->loop->count) >> 24) & 0xFF);
					}
				}

				fwrite(wavHeader, 1, 0x44, outFileTempRaw );

				delete [] wavHeader;
			}
			else
			{
				unsigned char* wavHeader = new unsigned char[0x44];
				for (int x = 0; x < 0x44; x++)
					wavHeader[x] = 0x00;

				wavHeader[0x0] = 0x73;
				wavHeader[0x1] = 0x6D;
				wavHeader[0x2] = 0x70;
				wavHeader[0x3] = 0x6C;
				wavHeader[0x4] = 0x3C;
				wavHeader[0x5] = 0x00;
				wavHeader[0x6] = 0x00;
				wavHeader[0x7] = 0x00;
				
				if (
						(alBank->soundBankFormat == SUPERMARIO64FORMAT)
						|| (alBank->soundBankFormat == MARIOKART64FORMAT) 
						|| (alBank->soundBankFormat == ZELDAFORMAT)
						|| (alBank->soundBankFormat == STARFOX64FORMAT)
						|| (alBank->soundBankFormat == FZEROFORMAT)
					)
				{
					float keybaseFloat = *reinterpret_cast<float*> (&alBank->eadPercussion[sound].keyBase);
					wavHeader[0x14] = ConvertEADGameValueToKeyBase(keybaseFloat);
				}
				else
					wavHeader[0x14] = 0x3C;
				wavHeader[0x15] = 0x00;
				wavHeader[0x16] = 0x00;
				wavHeader[0x17] = 0x00;

				fwrite(wavHeader, 1, 0x44, outFileTempRaw );

				delete [] wavHeader;
			}

			fclose(outFileTempRaw);

			delete [] outRawData;
			return true;
		}
	}
	return false;
}

bool CN64AIFCAudio::ExtractSfx(ALBank* alBank, int sound, CString outputFile, unsigned long samplingRate, bool ignoreKeyBase, bool halfSamplingRate)
{
	if (alBank->countSfx > 0)
	{
		float samplingRateFloat = (float)samplingRate;

		/*if (!ignoreKeyBase)
		{
			if (
						(alBank->soundBankFormat == SUPERMARIO64FORMAT)
						|| (alBank->soundBankFormat == MARIOKART64FORMAT) 
						|| (alBank->soundBankFormat == ZELDAFORMAT)
						|| (alBank->soundBankFormat == STARFOX64FORMAT)
						|| (alBank->soundBankFormat == FZEROFORMAT)
					)
			{
				samplingRateFloat = samplingRateFloat / (*reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->unknown3 == 0) ? 1 : *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->unknown3);
			}
		}*/

		if (halfSamplingRate)
		{
			samplingRateFloat = samplingRateFloat / 2;
		}


		if (alBank->alSfx[sound] != NULL)
		{
			if (alBank->alSfx[sound]->type == AL_RAW16_WAVE)
			{
				FILE* outFileTempRaw = fopen(outputFile, "wb");
				if (outFileTempRaw == NULL)
				{
					MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
					return false;
				}

				unsigned char* wavHeader = new unsigned char[0x28];


				wavHeader[0x0] = 0x52;
				wavHeader[0x1] = 0x49;
				wavHeader[0x2] = 0x46;
				wavHeader[0x3] = 0x46;
				unsigned long chunkSize = 0x28 + (alBank->alSfx[sound]->len-2) + 0x44 - 0x8;
				wavHeader[0x4] = ((chunkSize >> 0) & 0xFF);
				wavHeader[0x5] = ((chunkSize >> 8) & 0xFF);
				wavHeader[0x6] = ((chunkSize >> 16) & 0xFF);
				wavHeader[0x7] = ((chunkSize >> 24) & 0xFF);
				wavHeader[0x8] = 0x57;
				wavHeader[0x9] = 0x41;
				wavHeader[0xA] = 0x56;
				wavHeader[0xB] = 0x45;
				wavHeader[0xC] = 0x66;
				wavHeader[0xD] = 0x6D;
				wavHeader[0xE] = 0x74;
				wavHeader[0xF] = 0x20;
				wavHeader[0x10] = 0x10;
				wavHeader[0x11] = 0x00;
				wavHeader[0x12] = 0x00;
				wavHeader[0x13] = 0x00;
				wavHeader[0x14] = 0x01;
				wavHeader[0x15] = 0x00;
				wavHeader[0x16] = 0x01;
				wavHeader[0x17] = 0x00;
				wavHeader[0x18] = (((unsigned long)samplingRateFloat >> 0) & 0xFF);
				wavHeader[0x19] = (((unsigned long)samplingRateFloat >> 8) & 0xFF);
				wavHeader[0x1A] = (((unsigned long)samplingRateFloat >> 16) & 0xFF);
				wavHeader[0x1B] = (((unsigned long)samplingRateFloat >> 24) & 0xFF);
				wavHeader[0x1C] = ((((unsigned long)samplingRateFloat * 2) >> 0) & 0xFF);
				wavHeader[0x1D] = ((((unsigned long)samplingRateFloat * 2) >> 8) & 0xFF);
				wavHeader[0x1E] = ((((unsigned long)samplingRateFloat * 2) >> 16) & 0xFF);
				wavHeader[0x1F] = ((((unsigned long)samplingRateFloat * 2) >> 24) & 0xFF);
				wavHeader[0x20] = 0x02;
				wavHeader[0x21] = 0x00;
				wavHeader[0x22] = 0x10;
				wavHeader[0x23] = 0x00;
				wavHeader[0x24] = 0x64;
				wavHeader[0x25] = 0x61;
				wavHeader[0x26] = 0x74;
				wavHeader[0x27] = 0x61;

				fwrite(wavHeader, 1, 0x28, outFileTempRaw );

				delete [] wavHeader;

				unsigned long length = (alBank->alSfx[sound]->len-2);
				fwrite(&length, 1, 4, outFileTempRaw);

				fwrite(&alBank->alSfx[sound]->wavData[1], 1, (alBank->alSfx[sound]->len-2), outFileTempRaw);

				
				if (alBank->alSfx[sound]->rawWave->loop != NULL)
				{
					unsigned char* wavHeader = new unsigned char[0x44];
					for (int x = 0; x < 0x44; x++)
						wavHeader[x] = 0x00;

					wavHeader[0x0] = 0x73;
					wavHeader[0x1] = 0x6D;
					wavHeader[0x2] = 0x70;
					wavHeader[0x3] = 0x6C;
					wavHeader[0x4] = 0x3C;
					wavHeader[0x5] = 0x00;
					wavHeader[0x6] = 0x00;
					wavHeader[0x7] = 0x00;
					
					wavHeader[0x14] = 0x3C;
					wavHeader[0x15] = 0x00;
					wavHeader[0x16] = 0x00;
					wavHeader[0x17] = 0x00;
					
					wavHeader[0x24] = 0x01;
					wavHeader[0x25] = 0x00;
					wavHeader[0x26] = 0x00;
					wavHeader[0x27] = 0x00;

					if (alBank->alSfx[sound]->rawWave->loop->count > 0)
					{
						wavHeader[0x34] = ((alBank->alSfx[sound]->rawWave->loop->start >> 0) & 0xFF);
						wavHeader[0x35] = ((alBank->alSfx[sound]->rawWave->loop->start >> 8) & 0xFF);
						wavHeader[0x36] = ((alBank->alSfx[sound]->rawWave->loop->start >> 16) & 0xFF);
						wavHeader[0x37] = ((alBank->alSfx[sound]->rawWave->loop->start >> 24) & 0xFF);
						wavHeader[0x38] = (((alBank->alSfx[sound]->rawWave->loop->end) >> 0) & 0xFF);
						wavHeader[0x39] = (((alBank->alSfx[sound]->rawWave->loop->end) >> 8) & 0xFF);
						wavHeader[0x3A] = (((alBank->alSfx[sound]->rawWave->loop->end) >> 16) & 0xFF);
						wavHeader[0x3B] = (((alBank->alSfx[sound]->rawWave->loop->end) >> 24) & 0xFF);

						if (alBank->alSfx[sound]->rawWave->loop->count == 0xFFFFFFFF)
						{
							wavHeader[0x40] = 0x00;
							wavHeader[0x41] = 0x00;
							wavHeader[0x42] = 0x00;
							wavHeader[0x43] = 0x00;
						}
						else
						{
							wavHeader[0x40] = (((alBank->alSfx[sound]->rawWave->loop->count) >> 0) & 0xFF);
							wavHeader[0x41] = (((alBank->alSfx[sound]->rawWave->loop->count) >> 8) & 0xFF);
							wavHeader[0x42] = (((alBank->alSfx[sound]->rawWave->loop->count) >> 16) & 0xFF);
							wavHeader[0x43] = (((alBank->alSfx[sound]->rawWave->loop->count) >> 24) & 0xFF);
						}
					}

					fwrite(wavHeader, 1, 0x44, outFileTempRaw );

					delete [] wavHeader;
				}
				else
				{
					unsigned char* wavHeader = new unsigned char[0x44];
					for (int x = 0; x < 0x44; x++)
						wavHeader[x] = 0x00;

					wavHeader[0x0] = 0x73;
					wavHeader[0x1] = 0x6D;
					wavHeader[0x2] = 0x70;
					wavHeader[0x3] = 0x6C;
					wavHeader[0x4] = 0x3C;
					wavHeader[0x5] = 0x00;
					wavHeader[0x6] = 0x00;
					wavHeader[0x7] = 0x00;
					
					wavHeader[0x14] = 0x3C;
					wavHeader[0x15] = 0x00;
					wavHeader[0x16] = 0x00;
					wavHeader[0x17] = 0x00;

					fwrite(wavHeader, 1, 0x44, outFileTempRaw );

					delete [] wavHeader;
				}


				fclose(outFileTempRaw);

				return true;
			}
			else
			{
				// hack for mario kart
				if ((alBank->alSfx[sound]->adpcmWave == NULL) || (alBank->alSfx[sound]->adpcmWave->book == NULL))
					return false;

				signed short* outRawData = new signed short[alBank->alSfx[sound]->len * 4];
				int nSamples = decode(alBank->alSfx[sound]->wavData, outRawData, alBank->alSfx[sound]->len, alBank->alSfx[sound]->adpcmWave->book, alBank->alSfx[sound]->decode8Only);
				
				FILE* outFileTempRaw = fopen(outputFile, "wb");
				if (outFileTempRaw == NULL)
				{
					MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
					return false;
				}

				unsigned char* wavHeader = new unsigned char[0x28];


				wavHeader[0x0] = 0x52;
				wavHeader[0x1] = 0x49;
				wavHeader[0x2] = 0x46;
				wavHeader[0x3] = 0x46;
				unsigned long chunkSize = 0x28 + (nSamples * 2) + 0x44 - 0x8;
				wavHeader[0x4] = ((chunkSize >> 0) & 0xFF);
				wavHeader[0x5] = ((chunkSize >> 8) & 0xFF);
				wavHeader[0x6] = ((chunkSize >> 16) & 0xFF);
				wavHeader[0x7] = ((chunkSize >> 24) & 0xFF);
				wavHeader[0x8] = 0x57;
				wavHeader[0x9] = 0x41;
				wavHeader[0xA] = 0x56;
				wavHeader[0xB] = 0x45;
				wavHeader[0xC] = 0x66;
				wavHeader[0xD] = 0x6D;
				wavHeader[0xE] = 0x74;
				wavHeader[0xF] = 0x20;
				wavHeader[0x10] = 0x10;
				wavHeader[0x11] = 0x00;
				wavHeader[0x12] = 0x00;
				wavHeader[0x13] = 0x00;
				wavHeader[0x14] = 0x01;
				wavHeader[0x15] = 0x00;
				wavHeader[0x16] = 0x01;
				wavHeader[0x17] = 0x00;
				wavHeader[0x18] = ((samplingRate >> 0) & 0xFF);
				wavHeader[0x19] = ((samplingRate >> 8) & 0xFF);
				wavHeader[0x1A] = ((samplingRate >> 16) & 0xFF);
				wavHeader[0x1B] = ((samplingRate >> 24) & 0xFF);
				wavHeader[0x1C] = ((((unsigned long)samplingRateFloat * 2) >> 0) & 0xFF);
				wavHeader[0x1D] = ((((unsigned long)samplingRateFloat * 2) >> 8) & 0xFF);
				wavHeader[0x1E] = ((((unsigned long)samplingRateFloat * 2) >> 16) & 0xFF);
				wavHeader[0x1F] = ((((unsigned long)samplingRateFloat * 2) >> 24) & 0xFF);
				wavHeader[0x20] = 0x02;
				wavHeader[0x21] = 0x00;
				wavHeader[0x22] = 0x10;
				wavHeader[0x23] = 0x00;
				wavHeader[0x24] = 0x64;
				wavHeader[0x25] = 0x61;
				wavHeader[0x26] = 0x74;
				wavHeader[0x27] = 0x61;

				fwrite(wavHeader, 1, 0x28, outFileTempRaw );

				delete [] wavHeader;

				unsigned long length = (nSamples * 2);
				fwrite(&length, 1, 4, outFileTempRaw);

				for (int x = 0; x < nSamples; x++)
				{
					fwrite(&outRawData[x], 1,2, outFileTempRaw);
				}

				if (alBank->alSfx[sound]->adpcmWave->loop != NULL)
				{
					unsigned char* wavHeader = new unsigned char[0x44];
					for (int x = 0; x < 0x44; x++)
						wavHeader[x] = 0x00;

					wavHeader[0x0] = 0x73;
					wavHeader[0x1] = 0x6D;
					wavHeader[0x2] = 0x70;
					wavHeader[0x3] = 0x6C;
					wavHeader[0x4] = 0x3C;
					wavHeader[0x5] = 0x00;
					wavHeader[0x6] = 0x00;
					wavHeader[0x7] = 0x00;
					
					wavHeader[0x14] = 0x3C;
					wavHeader[0x15] = 0x00;
					wavHeader[0x16] = 0x00;
					wavHeader[0x17] = 0x00;
					
					wavHeader[0x24] = 0x01;
					wavHeader[0x25] = 0x00;
					wavHeader[0x26] = 0x00;
					wavHeader[0x27] = 0x00;

					if (alBank->alSfx[sound]->adpcmWave->loop->count > 0)
					{
						wavHeader[0x34] = ((alBank->alSfx[sound]->adpcmWave->loop->start >> 0) & 0xFF);
						wavHeader[0x35] = ((alBank->alSfx[sound]->adpcmWave->loop->start >> 8) & 0xFF);
						wavHeader[0x36] = ((alBank->alSfx[sound]->adpcmWave->loop->start >> 16) & 0xFF);
						wavHeader[0x37] = ((alBank->alSfx[sound]->adpcmWave->loop->start >> 24) & 0xFF);
						wavHeader[0x38] = (((alBank->alSfx[sound]->adpcmWave->loop->end) >> 0) & 0xFF);
						wavHeader[0x39] = (((alBank->alSfx[sound]->adpcmWave->loop->end) >> 8) & 0xFF);
						wavHeader[0x3A] = (((alBank->alSfx[sound]->adpcmWave->loop->end) >> 16) & 0xFF);
						wavHeader[0x3B] = (((alBank->alSfx[sound]->adpcmWave->loop->end) >> 24) & 0xFF);

						if (alBank->alSfx[sound]->adpcmWave->loop->count == 0xFFFFFFFF)
						{
							wavHeader[0x40] = 0x00;
							wavHeader[0x41] = 0x00;
							wavHeader[0x42] = 0x00;
							wavHeader[0x43] = 0x00;
						}
						else
						{
							wavHeader[0x40] = (((alBank->alSfx[sound]->adpcmWave->loop->count) >> 0) & 0xFF);
							wavHeader[0x41] = (((alBank->alSfx[sound]->adpcmWave->loop->count) >> 8) & 0xFF);
							wavHeader[0x42] = (((alBank->alSfx[sound]->adpcmWave->loop->count) >> 16) & 0xFF);
							wavHeader[0x43] = (((alBank->alSfx[sound]->adpcmWave->loop->count) >> 24) & 0xFF);
						}
					}

					fwrite(wavHeader, 1, 0x44, outFileTempRaw );

					delete [] wavHeader;
				}
				else
				{
					unsigned char* wavHeader = new unsigned char[0x44];
					for (int x = 0; x < 0x44; x++)
						wavHeader[x] = 0x00;

					wavHeader[0x0] = 0x73;
					wavHeader[0x1] = 0x6D;
					wavHeader[0x2] = 0x70;
					wavHeader[0x3] = 0x6C;
					wavHeader[0x4] = 0x3C;
					wavHeader[0x5] = 0x00;
					wavHeader[0x6] = 0x00;
					wavHeader[0x7] = 0x00;
					wavHeader[0x14] = 0x3C;
					wavHeader[0x15] = 0x00;
					wavHeader[0x16] = 0x00;
					wavHeader[0x17] = 0x00;

					fwrite(wavHeader, 1, 0x44, outFileTempRaw );

					delete [] wavHeader;
				}

				fclose(outFileTempRaw);

				delete [] outRawData;
				return true;
			}
		}
	}
	return false;
}

unsigned char CN64AIFCAudio::ConvertEADGameValueToKeyBase(float eadKeyvalue)
{
	float keybaseReal = (((eadKeyvalue - 0.0) < 0.00001) ? 1.0f : eadKeyvalue);

	float smallestDistance = 9999999999999.0f;
	unsigned char realKey = 0;

	for (int x = 0; x < 0x100; x++)
	{
		float distance = (fabs(keybaseReal - CN64AIFCAudio::keyTable[x]));

		if (distance < smallestDistance)
		{
			smallestDistance = distance;
			realKey = x;
		}
	}

	if (realKey > 0x7F)
		realKey = 0x7F;

	return realKey;
}

bool CN64AIFCAudio::ExtractRawPCMData(CString mainFolder, ALBank* alBank, int instrument, int sound, CString outputFile, byte primSel)
{
	if (alBank->inst[instrument]->soundCount > 0)
	{
		if (alBank->inst[instrument]->sounds[sound] != NULL)
		{
			ALWave* alWave = NULL;
			if (primSel == PRIMARY)
			{
				alWave = &alBank->inst[instrument]->sounds[sound]->wav;
			}
			else if (primSel == PREVIOUS)
			{
				alWave = &alBank->inst[instrument]->sounds[sound]->wavPrevious;
			}
			else if (primSel == SECONDARY)
			{
				alWave = &alBank->inst[instrument]->sounds[sound]->wavSecondary;
			}

			if (alWave->type == AL_RAW16_WAVE)
			{
				FILE* outFileTempRaw = fopen(outputFile, "wb");
				if (outFileTempRaw == NULL)
				{
					MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
					return false;
				}

				//unsigned long length = (alWave->len-2);
				//fwrite(&length, 1, 4, outFileTempRaw);

				fwrite(&alWave->wavData[1], 1, (alWave->len-2), outFileTempRaw);
				fclose(outFileTempRaw);
			}
			else if (alWave->type == AL_ADPCM_WAVE)
			{
				if ((alWave->adpcmWave == NULL) || (alWave->adpcmWave->book == NULL))
					return false;

				signed short* outRawData = new signed short[alWave->len * 4];
				int nSamples = decode(alWave->wavData, outRawData, alWave->len, alWave->adpcmWave->book, alWave->decode8Only);
				
				FILE* outFileTempRaw = fopen(outputFile, "wb");
				if (outFileTempRaw == NULL)
				{
					MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
					return false;
				}

				//unsigned long length = (nSamples * 2);
				//fwrite(&length, 1, 4, outFileTempRaw);

				for (int x = 0; x < nSamples; x++)
				{
					fwrite(&outRawData[x], 1,2, outFileTempRaw);
				}

				fclose(outFileTempRaw);

				delete [] outRawData;
			}
			else if (alWave->type == AL_VOX_WAVE)
			{
				// TODO better
				CString directory = outputFile.Mid(0, (outputFile.ReverseFind('\\')+1));

				FILE* outFileTemp = fopen(directory + "tempASA3d.vox", "wb");
				if (outFileTemp == NULL)
				{
					return false;
				}
				fwrite(alBank->inst[instrument]->sounds[sound]->wav.wavData, 1, alBank->inst[instrument]->sounds[sound]->wav.len, outFileTemp);
				fflush(outFileTemp);
				fclose(outFileTemp);

				::SetCurrentDirectory(mainFolder);

				CString tempStr;
				tempStr.Format("sox -r %d -c 1 \"%s\" -e signed -t wavpcm \"%s\"", alBank->inst[instrument]->samplerate, directory + "tempASA3d.vox", outputFile);
				hiddenExec(_T(tempStr.GetBuffer()), mainFolder);
			}
			// Full credit to Musyx goes to Bobby Smiles (from Mupen emulator)
			else if (alWave->type == AL_MUSYX_WAVE)
			{
				if ((alWave->adpcmWave == NULL) || (alWave->adpcmWave->book == NULL))
					return false;

				signed short* outRawData = new signed short[alWave->len * 4];
				int nSamples = decodemusyxadpcm(alWave->wavData, outRawData, alWave->len, alWave->adpcmWave->book);
				
				nSamples = alWave->sampleRateNotInDefaultNintendoSpec;

				FILE* outFileTempRaw = fopen(outputFile, "wb");
				if (outFileTempRaw == NULL)
				{
					MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
					return false;
				}

				//unsigned long length = (nSamples * 2);
				//fwrite(&length, 1, 4, outFileTempRaw);

				for (int x = 0; x < nSamples; x++)
				{
					fwrite(&outRawData[x], 1,2, outFileTempRaw);
				}

				fclose(outFileTempRaw);

				delete [] outRawData;
			}
			else if ((alWave->type == AL_SIGNED_RAW8) || (alWave->type == AL_SIGNED_RAW16))
			{
				int flags = (alWave->type == AL_SIGNED_RAW16);

				FILE* outFileTempRaw = fopen(outputFile, "wb");
				if (outFileTempRaw == NULL)
				{
					MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
					return false;
				}

				
				//unsigned long length = alWave->len;
				//fwrite(&length, 1, 4, outFileTempRaw);

				if ((flags & 1) == 1)
				{
					fwrite(&alWave->wavData, 1, alWave->len, outFileTempRaw);
				}
				else
				{
					for (int r = 0; r < alWave->len; r++)
					{
						int value = (signed char)alWave->wavData[r];
						value += 128;
						fwrite(&value, 1, 1, outFileTempRaw);

					}
				}

				fclose(outFileTempRaw);
			}

			return true;
		}
	}
	return false;
}

bool CN64AIFCAudio::ExtractPercussionRawPCMData(CString mainFolder, ALBank* alBank, int sound, CString outputFile)
{
	if (alBank->percussion->soundCount > 0)
	{
		if (alBank->percussion->sounds[sound] != NULL)
		{
			ALWave* alWave = &alBank->percussion->sounds[sound]->wav;

			if (alWave->type == AL_RAW16_WAVE)
			{
				FILE* outFileTempRaw = fopen(outputFile, "wb");
				if (outFileTempRaw == NULL)
				{
					MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
					return false;
				}

				//unsigned long length = (alWave->len-2);
				//fwrite(&length, 1, 4, outFileTempRaw);

				fwrite(&alWave->wavData[1], 1, (alWave->len-2), outFileTempRaw);
				fclose(outFileTempRaw);
			}
			else if (alWave->type == AL_ADPCM_WAVE)
			{
				if ((alWave->adpcmWave == NULL) || (alWave->adpcmWave->book == NULL))
					return false;

				signed short* outRawData = new signed short[alWave->len * 4];
				int nSamples = decode(alWave->wavData, outRawData, alWave->len, alWave->adpcmWave->book, alWave->decode8Only);
				
				FILE* outFileTempRaw = fopen(outputFile, "wb");
				if (outFileTempRaw == NULL)
				{
					MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
					return false;
				}

				//unsigned long length = (nSamples * 2);
				//fwrite(&length, 1, 4, outFileTempRaw);

				for (int x = 0; x < nSamples; x++)
				{
					fwrite(&outRawData[x], 1,2, outFileTempRaw);
				}

				fclose(outFileTempRaw);

				delete [] outRawData;
			}
			else if (alWave->type == AL_VOX_WAVE)
			{
				// TODO better
				CString directory = outputFile.Mid(0, (outputFile.ReverseFind('\\')+1));

				FILE* outFileTemp = fopen(directory + "tempASA3d.vox", "wb");
				if (outFileTemp == NULL)
				{
					return false;
				}
				fwrite(alBank->percussion->sounds[sound]->wav.wavData, 1, alBank->percussion->sounds[sound]->wav.len, outFileTemp);
				fflush(outFileTemp);
				fclose(outFileTemp);

				::SetCurrentDirectory(mainFolder);

				CString tempStr;
				tempStr.Format("sox -r %d -c 1 \"%s\" -e signed -t wavpcm \"%s\"", alBank->percussion->samplerate, directory + "tempASA3d.vox", outputFile);
				hiddenExec(_T(tempStr.GetBuffer()), mainFolder);
			}
			// Full credit to Musyx goes to Bobby Smiles (from Mupen emulator)
			else if (alWave->type == AL_MUSYX_WAVE)
			{
				if ((alWave->adpcmWave == NULL) || (alWave->adpcmWave->book == NULL))
					return false;

				signed short* outRawData = new signed short[alWave->len * 4];
				int nSamples = decodemusyxadpcm(alWave->wavData, outRawData, alWave->len, alWave->adpcmWave->book);
				
				nSamples = alWave->sampleRateNotInDefaultNintendoSpec;

				FILE* outFileTempRaw = fopen(outputFile, "wb");
				if (outFileTempRaw == NULL)
				{
					MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
					return false;
				}

				//unsigned long length = (nSamples * 2);
				//fwrite(&length, 1, 4, outFileTempRaw);

				for (int x = 0; x < nSamples; x++)
				{
					fwrite(&outRawData[x], 1,2, outFileTempRaw);
				}

				fclose(outFileTempRaw);

				delete [] outRawData;
			}
			else if ((alWave->type == AL_SIGNED_RAW8) || (alWave->type == AL_SIGNED_RAW16))
			{
				int flags = (alWave->type == AL_SIGNED_RAW16);

				FILE* outFileTempRaw = fopen(outputFile, "wb");
				if (outFileTempRaw == NULL)
				{
					MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
					return false;
				}

				
				//unsigned long length = alWave->len;
				//fwrite(&length, 1, 4, outFileTempRaw);

				if ((flags & 1) == 1)
				{
					fwrite(&alWave->wavData, 1, alWave->len, outFileTempRaw);
				}
				else
				{
					for (int r = 0; r < alWave->len; r++)
					{
						int value = (signed char)alWave->wavData[r];
						value += 128;
						fwrite(&value, 1, 1, outFileTempRaw);

					}
				}

				fclose(outFileTempRaw);
			}

			return true;
		}
	}
	return false;
}

bool CN64AIFCAudio::ExtractRawSound(CString mainFolder, ALBank* alBank, int instrument, int sound, CString outputFile, unsigned long samplingRate, byte primSel, bool ignoreKeyBase, bool halfSamplingRate)
{
	float samplingRateFloat = (float)samplingRate;

	if (alBank->inst[instrument]->soundCount > 0)
	{
		if (alBank->inst[instrument]->sounds[sound] != NULL)
		{
			ALWave* alWave = NULL;
			if (primSel == PRIMARY)
			{
				alWave = &alBank->inst[instrument]->sounds[sound]->wav;
			}
			else if (primSel == PREVIOUS)
			{
				alWave = &alBank->inst[instrument]->sounds[sound]->wavPrevious;
			}
			else if (primSel == SECONDARY)
			{
				alWave = &alBank->inst[instrument]->sounds[sound]->wavSecondary;
			}

			/*if (!ignoreKeyBase)
			{
				if (
					(alBank->soundBankFormat == STANDARDFORMAT)
					|| (alBank->soundBankFormat == STANDARDRNCCOMPRESSED)
					|| (alBank->soundBankFormat == STANDARDRNXCOMPRESSED)
					|| (alBank->soundBankFormat == BLASTCORPSZLBSTANDARD)
					|| (alBank->soundBankFormat == NINDEC)
					)
				{
					samplingRateFloat = samplingRateFloat / CN64AIFCAudio::keyTable[alBank->inst[instrument]->sounds[sound]->key.keybase];
				}
				else if (
						(alBank->soundBankFormat == SUPERMARIO64FORMAT)
						|| (alBank->soundBankFormat == MARIOKART64FORMAT) 
						|| (alBank->soundBankFormat == ZELDAFORMAT)
						|| (alBank->soundBankFormat == STARFOX64FORMAT)
						|| (alBank->soundBankFormat == FZEROFORMAT)
					)
				{
					samplingRateFloat = samplingRateFloat / (((*reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->unknown3) - 0.0) < 0.00001) ? 1.0f : *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->unknown3));
				}
			}*/

			if (halfSamplingRate)
			{
				samplingRateFloat = samplingRateFloat / 2;
			}

			if (alWave->type == AL_RAW16_WAVE)
			{
				FILE* outFileTempRaw = fopen(outputFile, "wb");
				if (outFileTempRaw == NULL)
				{
					MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
					return false;
				}

				unsigned char* wavHeader = new unsigned char[0x28];


				wavHeader[0x0] = 0x52;
				wavHeader[0x1] = 0x49;
				wavHeader[0x2] = 0x46;
				wavHeader[0x3] = 0x46;
				unsigned long chunkSize = 0x28 + (alWave->len-2) + 0x44 - 0x8;
				wavHeader[0x4] = ((chunkSize >> 0) & 0xFF);
				wavHeader[0x5] = ((chunkSize >> 8) & 0xFF);
				wavHeader[0x6] = ((chunkSize >> 16) & 0xFF);
				wavHeader[0x7] = ((chunkSize >> 24) & 0xFF);
				wavHeader[0x8] = 0x57;
				wavHeader[0x9] = 0x41;
				wavHeader[0xA] = 0x56;
				wavHeader[0xB] = 0x45;
				wavHeader[0xC] = 0x66;
				wavHeader[0xD] = 0x6D;
				wavHeader[0xE] = 0x74;
				wavHeader[0xF] = 0x20;
				wavHeader[0x10] = 0x10;
				wavHeader[0x11] = 0x00;
				wavHeader[0x12] = 0x00;
				wavHeader[0x13] = 0x00;
				wavHeader[0x14] = 0x01;
				wavHeader[0x15] = 0x00;
				wavHeader[0x16] = 0x01;
				wavHeader[0x17] = 0x00;
				wavHeader[0x18] = (((unsigned long)samplingRateFloat >> 0) & 0xFF);
				wavHeader[0x19] = (((unsigned long)samplingRateFloat >> 8) & 0xFF);
				wavHeader[0x1A] = (((unsigned long)samplingRateFloat >> 16) & 0xFF);
				wavHeader[0x1B] = (((unsigned long)samplingRateFloat >> 24) & 0xFF);
				wavHeader[0x1C] = ((((unsigned long)samplingRateFloat * 2) >> 0) & 0xFF);
				wavHeader[0x1D] = ((((unsigned long)samplingRateFloat * 2) >> 8) & 0xFF);
				wavHeader[0x1E] = ((((unsigned long)samplingRateFloat * 2) >> 16) & 0xFF);
				wavHeader[0x1F] = ((((unsigned long)samplingRateFloat * 2) >> 24) & 0xFF);
				wavHeader[0x20] = 0x02;
				wavHeader[0x21] = 0x00;
				wavHeader[0x22] = 0x10;
				wavHeader[0x23] = 0x00;
				wavHeader[0x24] = 0x64;
				wavHeader[0x25] = 0x61;
				wavHeader[0x26] = 0x74;
				wavHeader[0x27] = 0x61;

				fwrite(wavHeader, 1, 0x28, outFileTempRaw );

				delete [] wavHeader;

				unsigned long length = (alWave->len-2);
				fwrite(&length, 1, 4, outFileTempRaw);

				fwrite(&alWave->wavData[1], 1, (alWave->len-2), outFileTempRaw);

				
				if (alWave->rawWave->loop != NULL)
				{
					unsigned char* wavHeader = new unsigned char[0x44];
					for (int x = 0; x < 0x44; x++)
						wavHeader[x] = 0x00;

					wavHeader[0x0] = 0x73;
					wavHeader[0x1] = 0x6D;
					wavHeader[0x2] = 0x70;
					wavHeader[0x3] = 0x6C;
					wavHeader[0x4] = 0x3C;
					wavHeader[0x5] = 0x00;
					wavHeader[0x6] = 0x00;
					wavHeader[0x7] = 0x00;
					
					if (
						(alBank->soundBankFormat == SUPERMARIO64FORMAT)
						|| (alBank->soundBankFormat == MARIOKART64FORMAT) 
						|| (alBank->soundBankFormat == ZELDAFORMAT)
						|| (alBank->soundBankFormat == STARFOX64FORMAT)
						|| (alBank->soundBankFormat == FZEROFORMAT)
					)
					{
						float keybaseFloat;

						if (primSel == PRIMARY)
						{
							keybaseFloat = *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->floatKeyBase);
						}
						else if (primSel == PREVIOUS)
						{
							keybaseFloat = *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->floatKeyBasePrev);
						}
						else if (primSel == SECONDARY)
						{
							keybaseFloat = *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->floatKeyBaseSec);
						}
						
						wavHeader[0x14] = ConvertEADGameValueToKeyBase(keybaseFloat);
					}
					else if (alBank->inst[instrument]->sounds[sound]->key.keybase != 0)
						wavHeader[0x14] = alBank->inst[instrument]->sounds[sound]->key.keybase;//0x3C;
					else
						wavHeader[0x14] = 0x3C;
					wavHeader[0x15] = 0x00;
					wavHeader[0x16] = 0x00;
					wavHeader[0x17] = 0x00;
					
					wavHeader[0x24] = 0x01;
					wavHeader[0x25] = 0x00;
					wavHeader[0x26] = 0x00;
					wavHeader[0x27] = 0x00;

					if (alWave->rawWave->loop->count > 0)
					{
						wavHeader[0x34] = ((alWave->rawWave->loop->start >> 0) & 0xFF);
						wavHeader[0x35] = ((alWave->rawWave->loop->start >> 8) & 0xFF);
						wavHeader[0x36] = ((alWave->rawWave->loop->start >> 16) & 0xFF);
						wavHeader[0x37] = ((alWave->rawWave->loop->start >> 24) & 0xFF);
						wavHeader[0x38] = (((alWave->rawWave->loop->end) >> 0) & 0xFF);
						wavHeader[0x39] = (((alWave->rawWave->loop->end) >> 8) & 0xFF);
						wavHeader[0x3A] = (((alWave->rawWave->loop->end) >> 16) & 0xFF);
						wavHeader[0x3B] = (((alWave->rawWave->loop->end) >> 24) & 0xFF);

						if (alWave->rawWave->loop->count == 0xFFFFFFFF)
						{
							wavHeader[0x40] = 0x00;
							wavHeader[0x41] = 0x00;
							wavHeader[0x42] = 0x00;
							wavHeader[0x43] = 0x00;
						}
						else
						{
							wavHeader[0x40] = (((alWave->rawWave->loop->count) >> 0) & 0xFF);
							wavHeader[0x41] = (((alWave->rawWave->loop->count) >> 8) & 0xFF);
							wavHeader[0x42] = (((alWave->rawWave->loop->count) >> 16) & 0xFF);
							wavHeader[0x43] = (((alWave->rawWave->loop->count) >> 24) & 0xFF);
						}
					}

					fwrite(wavHeader, 1, 0x44, outFileTempRaw );

					delete [] wavHeader;
				}
				else
				{
					unsigned char* wavHeader = new unsigned char[0x44];
					for (int x = 0; x < 0x44; x++)
						wavHeader[x] = 0x00;

					wavHeader[0x0] = 0x73;
					wavHeader[0x1] = 0x6D;
					wavHeader[0x2] = 0x70;
					wavHeader[0x3] = 0x6C;
					wavHeader[0x4] = 0x3C;
					wavHeader[0x5] = 0x00;
					wavHeader[0x6] = 0x00;
					wavHeader[0x7] = 0x00;
					
					if (
						(alBank->soundBankFormat == SUPERMARIO64FORMAT)
						|| (alBank->soundBankFormat == MARIOKART64FORMAT) 
						|| (alBank->soundBankFormat == ZELDAFORMAT)
						|| (alBank->soundBankFormat == STARFOX64FORMAT)
						|| (alBank->soundBankFormat == FZEROFORMAT)
					)
					{
						float keybaseFloat;

						if (primSel == PRIMARY)
						{
							keybaseFloat = *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->floatKeyBase);
						}
						else if (primSel == PREVIOUS)
						{
							keybaseFloat = *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->floatKeyBasePrev);
						}
						else if (primSel == SECONDARY)
						{
							keybaseFloat = *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->floatKeyBaseSec);
						}
						
						wavHeader[0x14] = ConvertEADGameValueToKeyBase(keybaseFloat);
					}
					else if (alBank->inst[instrument]->sounds[sound]->key.keybase != 0)
						wavHeader[0x14] = alBank->inst[instrument]->sounds[sound]->key.keybase;//0x3C;
					else
						wavHeader[0x14] = 0x3C;
					wavHeader[0x15] = 0x00;
					wavHeader[0x16] = 0x00;
					wavHeader[0x17] = 0x00;

					fwrite(wavHeader, 1, 0x44, outFileTempRaw );

					delete [] wavHeader;
				}

				fclose(outFileTempRaw);
			}
			else if (alWave->type == AL_ADPCM_WAVE)
			{
				if ((alWave->adpcmWave == NULL) || (alWave->adpcmWave->book == NULL))
					return false;

				signed short* outRawData = new signed short[alWave->len * 4];
				int nSamples = decode(alWave->wavData, outRawData, alWave->len, alWave->adpcmWave->book, alWave->decode8Only);
				
				FILE* outFileTempRaw = fopen(outputFile, "wb");
				if (outFileTempRaw == NULL)
				{
					MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
					return false;
				}

				unsigned char* wavHeader = new unsigned char[0x28];


				wavHeader[0x0] = 0x52;
				wavHeader[0x1] = 0x49;
				wavHeader[0x2] = 0x46;
				wavHeader[0x3] = 0x46;
				unsigned long chunkSize = 0x28 + (nSamples * 2) + 0x44 - 0x8;
				wavHeader[0x4] = ((chunkSize >> 0) & 0xFF);
				wavHeader[0x5] = ((chunkSize >> 8) & 0xFF);
				wavHeader[0x6] = ((chunkSize >> 16) & 0xFF);
				wavHeader[0x7] = ((chunkSize >> 24) & 0xFF);
				wavHeader[0x8] = 0x57;
				wavHeader[0x9] = 0x41;
				wavHeader[0xA] = 0x56;
				wavHeader[0xB] = 0x45;
				wavHeader[0xC] = 0x66;
				wavHeader[0xD] = 0x6D;
				wavHeader[0xE] = 0x74;
				wavHeader[0xF] = 0x20;
				wavHeader[0x10] = 0x10;
				wavHeader[0x11] = 0x00;
				wavHeader[0x12] = 0x00;
				wavHeader[0x13] = 0x00;
				wavHeader[0x14] = 0x01;
				wavHeader[0x15] = 0x00;
				wavHeader[0x16] = 0x01;
				wavHeader[0x17] = 0x00;
				wavHeader[0x18] = (((unsigned long)samplingRateFloat >> 0) & 0xFF);
				wavHeader[0x19] = (((unsigned long)samplingRateFloat >> 8) & 0xFF);
				wavHeader[0x1A] = (((unsigned long)samplingRateFloat >> 16) & 0xFF);
				wavHeader[0x1B] = (((unsigned long)samplingRateFloat >> 24) & 0xFF);
				wavHeader[0x1C] = ((((unsigned long)samplingRateFloat * 2) >> 0) & 0xFF);
				wavHeader[0x1D] = ((((unsigned long)samplingRateFloat * 2) >> 8) & 0xFF);
				wavHeader[0x1E] = ((((unsigned long)samplingRateFloat * 2) >> 16) & 0xFF);
				wavHeader[0x1F] = ((((unsigned long)samplingRateFloat * 2) >> 24) & 0xFF);
				wavHeader[0x20] = 0x02;
				wavHeader[0x21] = 0x00;
				wavHeader[0x22] = 0x10;
				wavHeader[0x23] = 0x00;
				wavHeader[0x24] = 0x64;
				wavHeader[0x25] = 0x61;
				wavHeader[0x26] = 0x74;
				wavHeader[0x27] = 0x61;

				fwrite(wavHeader, 1, 0x28, outFileTempRaw );

				delete [] wavHeader;

				unsigned long length = (nSamples * 2);
				fwrite(&length, 1, 4, outFileTempRaw);

				for (int x = 0; x < nSamples; x++)
				{
					fwrite(&outRawData[x], 1,2, outFileTempRaw);
				}

				if (alWave->adpcmWave->loop != NULL)
				{
					unsigned char* wavHeader = new unsigned char[0x44];
					for (int x = 0; x < 0x44; x++)
						wavHeader[x] = 0x00;

					wavHeader[0x0] = 0x73;
					wavHeader[0x1] = 0x6D;
					wavHeader[0x2] = 0x70;
					wavHeader[0x3] = 0x6C;
					wavHeader[0x4] = 0x3C;
					wavHeader[0x5] = 0x00;
					wavHeader[0x6] = 0x00;
					wavHeader[0x7] = 0x00;
					
					if (
						(alBank->soundBankFormat == SUPERMARIO64FORMAT)
						|| (alBank->soundBankFormat == MARIOKART64FORMAT) 
						|| (alBank->soundBankFormat == ZELDAFORMAT)
						|| (alBank->soundBankFormat == STARFOX64FORMAT)
						|| (alBank->soundBankFormat == FZEROFORMAT)
					)
					{
						float keybaseFloat;

						if (primSel == PRIMARY)
						{
							keybaseFloat = *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->floatKeyBase);
						}
						else if (primSel == PREVIOUS)
						{
							keybaseFloat = *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->floatKeyBasePrev);
						}
						else if (primSel == SECONDARY)
						{
							keybaseFloat = *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->floatKeyBaseSec);
						}
						
						wavHeader[0x14] = ConvertEADGameValueToKeyBase(keybaseFloat);
					}
					else if (alBank->inst[instrument]->sounds[sound]->key.keybase != 0)
						wavHeader[0x14] = alBank->inst[instrument]->sounds[sound]->key.keybase;//0x3C;
					else
						wavHeader[0x14] = 0x3C;
					wavHeader[0x15] = 0x00;
					wavHeader[0x16] = 0x00;
					wavHeader[0x17] = 0x00;
					
					wavHeader[0x24] = 0x01;
					wavHeader[0x25] = 0x00;
					wavHeader[0x26] = 0x00;
					wavHeader[0x27] = 0x00;

					if (alWave->adpcmWave->loop->count > 0)
					{
						wavHeader[0x34] = ((alWave->adpcmWave->loop->start >> 0) & 0xFF);
						wavHeader[0x35] = ((alWave->adpcmWave->loop->start >> 8) & 0xFF);
						wavHeader[0x36] = ((alWave->adpcmWave->loop->start >> 16) & 0xFF);
						wavHeader[0x37] = ((alWave->adpcmWave->loop->start >> 24) & 0xFF);
						wavHeader[0x38] = (((alWave->adpcmWave->loop->end) >> 0) & 0xFF);
						wavHeader[0x39] = (((alWave->adpcmWave->loop->end) >> 8) & 0xFF);
						wavHeader[0x3A] = (((alWave->adpcmWave->loop->end) >> 16) & 0xFF);
						wavHeader[0x3B] = (((alWave->adpcmWave->loop->end) >> 24) & 0xFF);

						if (alWave->adpcmWave->loop->count == 0xFFFFFFFF)
						{
							wavHeader[0x40] = 0x00;
							wavHeader[0x41] = 0x00;
							wavHeader[0x42] = 0x00;
							wavHeader[0x43] = 0x00;
						}
						else
						{
							wavHeader[0x40] = (((alWave->adpcmWave->loop->count) >> 0) & 0xFF);
							wavHeader[0x41] = (((alWave->adpcmWave->loop->count) >> 8) & 0xFF);
							wavHeader[0x42] = (((alWave->adpcmWave->loop->count) >> 16) & 0xFF);
							wavHeader[0x43] = (((alWave->adpcmWave->loop->count) >> 24) & 0xFF);
						}
					}


					fwrite(wavHeader, 1, 0x44, outFileTempRaw );

					delete [] wavHeader;
				}
				else
				{
					unsigned char* wavHeader = new unsigned char[0x44];
					for (int x = 0; x < 0x44; x++)
						wavHeader[x] = 0x00;

					wavHeader[0x0] = 0x73;
					wavHeader[0x1] = 0x6D;
					wavHeader[0x2] = 0x70;
					wavHeader[0x3] = 0x6C;
					wavHeader[0x4] = 0x3C;
					wavHeader[0x5] = 0x00;
					wavHeader[0x6] = 0x00;
					wavHeader[0x7] = 0x00;
					
					if (
						(alBank->soundBankFormat == SUPERMARIO64FORMAT)
						|| (alBank->soundBankFormat == MARIOKART64FORMAT) 
						|| (alBank->soundBankFormat == ZELDAFORMAT)
						|| (alBank->soundBankFormat == STARFOX64FORMAT)
						|| (alBank->soundBankFormat == FZEROFORMAT)
					)
					{
						float keybaseFloat;

						if (primSel == PRIMARY)
						{
							keybaseFloat = *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->floatKeyBase);
						}
						else if (primSel == PREVIOUS)
						{
							keybaseFloat = *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->floatKeyBasePrev);
						}
						else if (primSel == SECONDARY)
						{
							keybaseFloat = *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->floatKeyBaseSec);
						}
						
						wavHeader[0x14] = ConvertEADGameValueToKeyBase(keybaseFloat);
					}
					else if (alBank->inst[instrument]->sounds[sound]->key.keybase != 0)
						wavHeader[0x14] = alBank->inst[instrument]->sounds[sound]->key.keybase;//0x3C;
					else
						wavHeader[0x14] = 0x3C;
					wavHeader[0x15] = 0x00;
					wavHeader[0x16] = 0x00;
					wavHeader[0x17] = 0x00;

					fwrite(wavHeader, 1, 0x44, outFileTempRaw );

					delete [] wavHeader;
				}

				fclose(outFileTempRaw);

				delete [] outRawData;
			}
			else if (alWave->type == AL_VOX_WAVE)
			{
				CString directory = outputFile.Mid(0, (outputFile.ReverseFind('\\')+1));

				FILE* outFileTemp = fopen(directory + "tempASA3d.vox", "wb");
				if (outFileTemp == NULL)
				{
					return false;
				}
				fwrite(alBank->inst[instrument]->sounds[sound]->wav.wavData, 1, alBank->inst[instrument]->sounds[sound]->wav.len, outFileTemp);
				fflush(outFileTemp);
				fclose(outFileTemp);

				::SetCurrentDirectory(mainFolder);

				CString tempStr;
				tempStr.Format("sox -r %d -c 1 \"%s\" -e signed -t wavpcm \"%s\"", alBank->inst[instrument]->samplerate, directory + "tempASA3d.vox", outputFile);
				hiddenExec(_T(tempStr.GetBuffer()), mainFolder);
			}
			// Full credit to Musyx goes to Bobby Smiles (from Mupen emulator)
			else if (alWave->type == AL_MUSYX_WAVE)
			{
				if ((alWave->adpcmWave == NULL) || (alWave->adpcmWave->book == NULL))
					return false;

				signed short* outRawData = new signed short[alWave->len * 4];
				int nSamples = decodemusyxadpcm(alWave->wavData, outRawData, alWave->len, alWave->adpcmWave->book);
				
				nSamples = alWave->sampleRateNotInDefaultNintendoSpec;

				FILE* outFileTempRaw = fopen(outputFile, "wb");
				if (outFileTempRaw == NULL)
				{
					MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
					return false;
				}

				unsigned char* wavHeader = new unsigned char[0x28];


				wavHeader[0x0] = 0x52;
				wavHeader[0x1] = 0x49;
				wavHeader[0x2] = 0x46;
				wavHeader[0x3] = 0x46;
				unsigned long chunkSize = 0x28 + (nSamples * 2) + 0x44 - 0x8;
				wavHeader[0x4] = ((chunkSize >> 0) & 0xFF);
				wavHeader[0x5] = ((chunkSize >> 8) & 0xFF);
				wavHeader[0x6] = ((chunkSize >> 16) & 0xFF);
				wavHeader[0x7] = ((chunkSize >> 24) & 0xFF);
				wavHeader[0x8] = 0x57;
				wavHeader[0x9] = 0x41;
				wavHeader[0xA] = 0x56;
				wavHeader[0xB] = 0x45;
				wavHeader[0xC] = 0x66;
				wavHeader[0xD] = 0x6D;
				wavHeader[0xE] = 0x74;
				wavHeader[0xF] = 0x20;
				wavHeader[0x10] = 0x10;
				wavHeader[0x11] = 0x00;
				wavHeader[0x12] = 0x00;
				wavHeader[0x13] = 0x00;
				wavHeader[0x14] = 0x01;
				wavHeader[0x15] = 0x00;
				wavHeader[0x16] = 0x01;
				wavHeader[0x17] = 0x00;
				wavHeader[0x18] = (((unsigned long)samplingRateFloat >> 0) & 0xFF);
				wavHeader[0x19] = (((unsigned long)samplingRateFloat >> 8) & 0xFF);
				wavHeader[0x1A] = (((unsigned long)samplingRateFloat >> 16) & 0xFF);
				wavHeader[0x1B] = (((unsigned long)samplingRateFloat >> 24) & 0xFF);
				wavHeader[0x1C] = ((((unsigned long)samplingRateFloat * 2) >> 0) & 0xFF);
				wavHeader[0x1D] = ((((unsigned long)samplingRateFloat * 2) >> 8) & 0xFF);
				wavHeader[0x1E] = ((((unsigned long)samplingRateFloat * 2) >> 16) & 0xFF);
				wavHeader[0x1F] = ((((unsigned long)samplingRateFloat * 2) >> 24) & 0xFF);
				wavHeader[0x20] = 0x02;
				wavHeader[0x21] = 0x00;
				wavHeader[0x22] = 0x10;
				wavHeader[0x23] = 0x00;
				wavHeader[0x24] = 0x64;
				wavHeader[0x25] = 0x61;
				wavHeader[0x26] = 0x74;
				wavHeader[0x27] = 0x61;

				fwrite(wavHeader, 1, 0x28, outFileTempRaw );

				delete [] wavHeader;

				unsigned long length = (nSamples * 2);
				fwrite(&length, 1, 4, outFileTempRaw);

				for (int x = 0; x < nSamples; x++)
				{
					fwrite(&outRawData[x], 1,2, outFileTempRaw);
				}

				if (alWave->adpcmWave->loop != NULL)
				{
					unsigned char* wavHeader = new unsigned char[0x44];
					for (int x = 0; x < 0x44; x++)
						wavHeader[x] = 0x00;

					wavHeader[0x0] = 0x73;
					wavHeader[0x1] = 0x6D;
					wavHeader[0x2] = 0x70;
					wavHeader[0x3] = 0x6C;
					wavHeader[0x4] = 0x3C;
					wavHeader[0x5] = 0x00;
					wavHeader[0x6] = 0x00;
					wavHeader[0x7] = 0x00;
					
					if (
						(alBank->soundBankFormat == SUPERMARIO64FORMAT)
						|| (alBank->soundBankFormat == MARIOKART64FORMAT) 
						|| (alBank->soundBankFormat == ZELDAFORMAT)
						|| (alBank->soundBankFormat == STARFOX64FORMAT)
						|| (alBank->soundBankFormat == FZEROFORMAT)
					)
					{
						float keybaseFloat;

						if (primSel == PRIMARY)
						{
							keybaseFloat = *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->floatKeyBase);
						}
						else if (primSel == PREVIOUS)
						{
							keybaseFloat = *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->floatKeyBasePrev);
						}
						else if (primSel == SECONDARY)
						{
							keybaseFloat = *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->floatKeyBaseSec);
						}
						
						wavHeader[0x14] = ConvertEADGameValueToKeyBase(keybaseFloat);
					}
					else if (alBank->inst[instrument]->sounds[sound]->key.keybase != 0)
						wavHeader[0x14] = alBank->inst[instrument]->sounds[sound]->key.keybase;//0x3C;
					else
						wavHeader[0x14] = 0x3C;
					wavHeader[0x15] = 0x00;
					wavHeader[0x16] = 0x00;
					wavHeader[0x17] = 0x00;
					
					wavHeader[0x24] = 0x01;
					wavHeader[0x25] = 0x00;
					wavHeader[0x26] = 0x00;
					wavHeader[0x27] = 0x00;

					if (alWave->adpcmWave->loop->count > 0)
					{
						wavHeader[0x34] = ((alWave->adpcmWave->loop->start >> 0) & 0xFF);
						wavHeader[0x35] = ((alWave->adpcmWave->loop->start >> 8) & 0xFF);
						wavHeader[0x36] = ((alWave->adpcmWave->loop->start >> 16) & 0xFF);
						wavHeader[0x37] = ((alWave->adpcmWave->loop->start >> 24) & 0xFF);
						wavHeader[0x38] = (((alWave->adpcmWave->loop->end) >> 0) & 0xFF);
						wavHeader[0x39] = (((alWave->adpcmWave->loop->end) >> 8) & 0xFF);
						wavHeader[0x3A] = (((alWave->adpcmWave->loop->end) >> 16) & 0xFF);
						wavHeader[0x3B] = (((alWave->adpcmWave->loop->end) >> 24) & 0xFF);

						if (alWave->adpcmWave->loop->count == 0xFFFFFFFF)
						{
							wavHeader[0x40] = 0x00;
							wavHeader[0x41] = 0x00;
							wavHeader[0x42] = 0x00;
							wavHeader[0x43] = 0x00;
						}
						else
						{
							wavHeader[0x40] = (((alWave->adpcmWave->loop->count) >> 0) & 0xFF);
							wavHeader[0x41] = (((alWave->adpcmWave->loop->count) >> 8) & 0xFF);
							wavHeader[0x42] = (((alWave->adpcmWave->loop->count) >> 16) & 0xFF);
							wavHeader[0x43] = (((alWave->adpcmWave->loop->count) >> 24) & 0xFF);
						}
					}


					fwrite(wavHeader, 1, 0x44, outFileTempRaw );

					delete [] wavHeader;
				}
				else
				{
					unsigned char* wavHeader = new unsigned char[0x44];
					for (int x = 0; x < 0x44; x++)
						wavHeader[x] = 0x00;

					wavHeader[0x0] = 0x73;
					wavHeader[0x1] = 0x6D;
					wavHeader[0x2] = 0x70;
					wavHeader[0x3] = 0x6C;
					wavHeader[0x4] = 0x3C;
					wavHeader[0x5] = 0x00;
					wavHeader[0x6] = 0x00;
					wavHeader[0x7] = 0x00;
					
					if (
						(alBank->soundBankFormat == SUPERMARIO64FORMAT)
						|| (alBank->soundBankFormat == MARIOKART64FORMAT) 
						|| (alBank->soundBankFormat == ZELDAFORMAT)
						|| (alBank->soundBankFormat == STARFOX64FORMAT)
						|| (alBank->soundBankFormat == FZEROFORMAT)
					)
					{
						float keybaseFloat;

						if (primSel == PRIMARY)
						{
							keybaseFloat = *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->floatKeyBase);
						}
						else if (primSel == PREVIOUS)
						{
							keybaseFloat = *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->floatKeyBasePrev);
						}
						else if (primSel == SECONDARY)
						{
							keybaseFloat = *reinterpret_cast<float*> (&alBank->inst[instrument]->sounds[sound]->floatKeyBaseSec);
						}
						
						wavHeader[0x14] = ConvertEADGameValueToKeyBase(keybaseFloat);
					}
					else if (alBank->inst[instrument]->sounds[sound]->key.keybase != 0)
						wavHeader[0x14] = alBank->inst[instrument]->sounds[sound]->key.keybase;//0x3C;
					else
						wavHeader[0x14] = 0x3C;
					wavHeader[0x15] = 0x00;
					wavHeader[0x16] = 0x00;
					wavHeader[0x17] = 0x00;

					fwrite(wavHeader, 1, 0x44, outFileTempRaw );

					delete [] wavHeader;
				}

				fclose(outFileTempRaw);

				delete [] outRawData;
			}
			else if ((alWave->type == AL_SIGNED_RAW8) || (alWave->type == AL_SIGNED_RAW16))
			{
				int flags = (alWave->type == AL_SIGNED_RAW16);

				FILE* outFileTempRaw = fopen(outputFile, "wb");
				if (outFileTempRaw == NULL)
				{
					MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
					return false;
				}

				unsigned char wavHeader[0x28];

				wavHeader[0x0] = 0x52;
				wavHeader[0x1] = 0x49;
				wavHeader[0x2] = 0x46;
				wavHeader[0x3] = 0x46;
				unsigned long chunkSize = 0x28 + alWave->len + 0x44 - 0x8;
				wavHeader[0x4] = ((chunkSize >> 0) & 0xFF);
				wavHeader[0x5] = ((chunkSize >> 8) & 0xFF);
				wavHeader[0x6] = ((chunkSize >> 16) & 0xFF);
				wavHeader[0x7] = ((chunkSize >> 24) & 0xFF);
				wavHeader[0x8] = 0x57;
				wavHeader[0x9] = 0x41;
				wavHeader[0xA] = 0x56;
				wavHeader[0xB] = 0x45;
				wavHeader[0xC] = 0x66;
				wavHeader[0xD] = 0x6D;
				wavHeader[0xE] = 0x74;
				wavHeader[0xF] = 0x20;
				wavHeader[0x10] = 0x10;
				wavHeader[0x11] = 0x00;
				wavHeader[0x12] = 0x00;
				wavHeader[0x13] = 0x00;
				wavHeader[0x14] = 0x01;
				wavHeader[0x15] = 0x00;
				wavHeader[0x16] = 0x01;
				wavHeader[0x17] = 0x00;
				wavHeader[0x18] = (((unsigned long)samplingRateFloat >> 0) & 0xFF);
				wavHeader[0x19] = (((unsigned long)samplingRateFloat >> 8) & 0xFF);
				wavHeader[0x1A] = (((unsigned long)samplingRateFloat >> 16) & 0xFF);
				wavHeader[0x1B] = (((unsigned long)samplingRateFloat >> 24) & 0xFF);
				wavHeader[0x1C] = ((((unsigned long)samplingRateFloat * (1 + (flags & 1))) >> 0) & 0xFF);
				wavHeader[0x1D] = ((((unsigned long)samplingRateFloat * (1 + (flags & 1))) >> 8) & 0xFF);
				wavHeader[0x1E] = ((((unsigned long)samplingRateFloat * (1 + (flags & 1))) >> 16) & 0xFF);
				wavHeader[0x1F] = ((((unsigned long)samplingRateFloat * (1 + (flags & 1))) >> 24) & 0xFF);
				wavHeader[0x20] = (1 + (flags & 1));
				wavHeader[0x21] = 0x00;
				wavHeader[0x22] = (((flags & 1) + 1) * 8);
				wavHeader[0x23] = 0x00;
				wavHeader[0x24] = 0x64;
				wavHeader[0x25] = 0x61;
				wavHeader[0x26] = 0x74;
				wavHeader[0x27] = 0x61;

				fwrite(wavHeader, 1, 0x28, outFileTempRaw );

				unsigned long length = alWave->len;
				fwrite(&length, 1, 4, outFileTempRaw);

				if ((flags & 1) == 1)
				{
					fwrite(&alWave->wavData, 1, alWave->len, outFileTempRaw);
				}
				else
				{
					for (int r = 0; r < alWave->len; r++)
					{
						int value = (signed char)alWave->wavData[r];
						value += 128;
						fwrite(&value, 1, 1, outFileTempRaw);

					}
				}

				fclose(outFileTempRaw);
			}

			return true;

		}
	}
	return false;
}

bool CN64AIFCAudio::ExtractPercussion(CString mainFolder, ALBank* alBank, int sound, CString outputFile, unsigned long samplingRate, bool ignoreKeyBase, bool halfSamplingRate)
{
	float samplingRateFloat = (float)samplingRate;

	if (alBank->percussion->soundCount > 0)
	{
		if (alBank->percussion->sounds[sound] != NULL)
		{
			ALWave* alWave = &alBank->percussion->sounds[sound]->wav;

			/*if (!ignoreKeyBase)
			{
				if (
					(alBank->soundBankFormat == STANDARDFORMAT)
					|| (alBank->soundBankFormat == STANDARDRNCCOMPRESSED)
					|| (alBank->soundBankFormat == STANDARDRNXCOMPRESSED)
					|| (alBank->soundBankFormat == BLASTCORPSZLBSTANDARD)
					|| (alBank->soundBankFormat == NINDEC)
					)
				{
					samplingRateFloat = samplingRateFloat / CN64AIFCAudio::keyTable[alBank->percussion->sounds[sound]->key.keybase];
				}
				else if (
						(alBank->soundBankFormat == SUPERMARIO64FORMAT)
						|| (alBank->soundBankFormat == MARIOKART64FORMAT) 
						|| (alBank->soundBankFormat == ZELDAFORMAT)
						|| (alBank->soundBankFormat == STARFOX64FORMAT)
						|| (alBank->soundBankFormat == FZEROFORMAT)
					)
				{
					samplingRateFloat = samplingRateFloat / (((*reinterpret_cast<float*> (&alBank->percussion->sounds[sound]->unknown3) - 0.0) < 0.00001) ? 1.0f : *reinterpret_cast<float*> (&alBank->percussion->sounds[sound]->unknown3));
				}
			}*/

			if (halfSamplingRate)
			{
				samplingRateFloat = samplingRateFloat / 2;
			}

			if (alWave->type == AL_RAW16_WAVE)
			{
				FILE* outFileTempRaw = fopen(outputFile, "wb");
				if (outFileTempRaw == NULL)
				{
					MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
					return false;
				}

				unsigned char* wavHeader = new unsigned char[0x28];


				wavHeader[0x0] = 0x52;
				wavHeader[0x1] = 0x49;
				wavHeader[0x2] = 0x46;
				wavHeader[0x3] = 0x46;
				unsigned long chunkSize = 0x28 + (alWave->len-2) + 0x44 - 0x8;
				wavHeader[0x4] = ((chunkSize >> 0) & 0xFF);
				wavHeader[0x5] = ((chunkSize >> 8) & 0xFF);
				wavHeader[0x6] = ((chunkSize >> 16) & 0xFF);
				wavHeader[0x7] = ((chunkSize >> 24) & 0xFF);
				wavHeader[0x8] = 0x57;
				wavHeader[0x9] = 0x41;
				wavHeader[0xA] = 0x56;
				wavHeader[0xB] = 0x45;
				wavHeader[0xC] = 0x66;
				wavHeader[0xD] = 0x6D;
				wavHeader[0xE] = 0x74;
				wavHeader[0xF] = 0x20;
				wavHeader[0x10] = 0x10;
				wavHeader[0x11] = 0x00;
				wavHeader[0x12] = 0x00;
				wavHeader[0x13] = 0x00;
				wavHeader[0x14] = 0x01;
				wavHeader[0x15] = 0x00;
				wavHeader[0x16] = 0x01;
				wavHeader[0x17] = 0x00;
				wavHeader[0x18] = (((unsigned long)samplingRateFloat >> 0) & 0xFF);
				wavHeader[0x19] = (((unsigned long)samplingRateFloat >> 8) & 0xFF);
				wavHeader[0x1A] = (((unsigned long)samplingRateFloat >> 16) & 0xFF);
				wavHeader[0x1B] = (((unsigned long)samplingRateFloat >> 24) & 0xFF);
				wavHeader[0x1C] = ((((unsigned long)samplingRateFloat * 2) >> 0) & 0xFF);
				wavHeader[0x1D] = ((((unsigned long)samplingRateFloat * 2) >> 8) & 0xFF);
				wavHeader[0x1E] = ((((unsigned long)samplingRateFloat * 2) >> 16) & 0xFF);
				wavHeader[0x1F] = ((((unsigned long)samplingRateFloat * 2) >> 24) & 0xFF);
				wavHeader[0x20] = 0x02;
				wavHeader[0x21] = 0x00;
				wavHeader[0x22] = 0x10;
				wavHeader[0x23] = 0x00;
				wavHeader[0x24] = 0x64;
				wavHeader[0x25] = 0x61;
				wavHeader[0x26] = 0x74;
				wavHeader[0x27] = 0x61;

				fwrite(wavHeader, 1, 0x28, outFileTempRaw );

				delete [] wavHeader;

				unsigned long length = (alWave->len-2);
				fwrite(&length, 1, 4, outFileTempRaw);

				fwrite(&alWave->wavData[1], 1, (alWave->len-2), outFileTempRaw);

				
				if (alWave->rawWave->loop != NULL)
				{
					unsigned char* wavHeader = new unsigned char[0x44];
					for (int x = 0; x < 0x44; x++)
						wavHeader[x] = 0x00;

					wavHeader[0x0] = 0x73;
					wavHeader[0x1] = 0x6D;
					wavHeader[0x2] = 0x70;
					wavHeader[0x3] = 0x6C;
					wavHeader[0x4] = 0x3C;
					wavHeader[0x5] = 0x00;
					wavHeader[0x6] = 0x00;
					wavHeader[0x7] = 0x00;
					
					if (alBank->percussion->sounds[sound]->key.keybase != 0)
						wavHeader[0x14] = alBank->percussion->sounds[sound]->key.keybase;//0x3C;
					else
						wavHeader[0x14] = 0x3C;
					wavHeader[0x15] = 0x00;
					wavHeader[0x16] = 0x00;
					wavHeader[0x17] = 0x00;
					
					wavHeader[0x24] = 0x01;
					wavHeader[0x25] = 0x00;
					wavHeader[0x26] = 0x00;
					wavHeader[0x27] = 0x00;

					if (alWave->rawWave->loop->count > 0)
					{
						wavHeader[0x34] = ((alWave->rawWave->loop->start >> 0) & 0xFF);
						wavHeader[0x35] = ((alWave->rawWave->loop->start >> 8) & 0xFF);
						wavHeader[0x36] = ((alWave->rawWave->loop->start >> 16) & 0xFF);
						wavHeader[0x37] = ((alWave->rawWave->loop->start >> 24) & 0xFF);
						wavHeader[0x38] = (((alWave->rawWave->loop->end) >> 0) & 0xFF);
						wavHeader[0x39] = (((alWave->rawWave->loop->end) >> 8) & 0xFF);
						wavHeader[0x3A] = (((alWave->rawWave->loop->end) >> 16) & 0xFF);
						wavHeader[0x3B] = (((alWave->rawWave->loop->end) >> 24) & 0xFF);

						if (alWave->rawWave->loop->count == 0xFFFFFFFF)
						{
							wavHeader[0x40] = 0x00;
							wavHeader[0x41] = 0x00;
							wavHeader[0x42] = 0x00;
							wavHeader[0x43] = 0x00;
						}
						else
						{
							wavHeader[0x40] = (((alWave->rawWave->loop->count) >> 0) & 0xFF);
							wavHeader[0x41] = (((alWave->rawWave->loop->count) >> 8) & 0xFF);
							wavHeader[0x42] = (((alWave->rawWave->loop->count) >> 16) & 0xFF);
							wavHeader[0x43] = (((alWave->rawWave->loop->count) >> 24) & 0xFF);
						}
					}

					fwrite(wavHeader, 1, 0x44, outFileTempRaw );

					delete [] wavHeader;
				}
				else
				{
					unsigned char* wavHeader = new unsigned char[0x44];
					for (int x = 0; x < 0x44; x++)
						wavHeader[x] = 0x00;

					wavHeader[0x0] = 0x73;
					wavHeader[0x1] = 0x6D;
					wavHeader[0x2] = 0x70;
					wavHeader[0x3] = 0x6C;
					wavHeader[0x4] = 0x3C;
					wavHeader[0x5] = 0x00;
					wavHeader[0x6] = 0x00;
					wavHeader[0x7] = 0x00;
					
					if (alBank->percussion->sounds[sound]->key.keybase != 0)
						wavHeader[0x14] = alBank->percussion->sounds[sound]->key.keybase;//0x3C;
					else
						wavHeader[0x14] = 0x3C;
					wavHeader[0x15] = 0x00;
					wavHeader[0x16] = 0x00;
					wavHeader[0x17] = 0x00;

					fwrite(wavHeader, 1, 0x44, outFileTempRaw );

					delete [] wavHeader;
				}

				fclose(outFileTempRaw);
			}
			else if (alWave->type == AL_ADPCM_WAVE)
			{
				if ((alWave->adpcmWave == NULL) || (alWave->adpcmWave->book == NULL))
					return false;

				signed short* outRawData = new signed short[alWave->len * 4];
				int nSamples = decode(alWave->wavData, outRawData, alWave->len, alWave->adpcmWave->book, alWave->decode8Only);
				
				FILE* outFileTempRaw = fopen(outputFile, "wb");
				if (outFileTempRaw == NULL)
				{
					MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
					return false;
				}

				unsigned char* wavHeader = new unsigned char[0x28];


				wavHeader[0x0] = 0x52;
				wavHeader[0x1] = 0x49;
				wavHeader[0x2] = 0x46;
				wavHeader[0x3] = 0x46;
				unsigned long chunkSize = 0x28 + (nSamples * 2) + 0x44 - 0x8;
				wavHeader[0x4] = ((chunkSize >> 0) & 0xFF);
				wavHeader[0x5] = ((chunkSize >> 8) & 0xFF);
				wavHeader[0x6] = ((chunkSize >> 16) & 0xFF);
				wavHeader[0x7] = ((chunkSize >> 24) & 0xFF);
				wavHeader[0x8] = 0x57;
				wavHeader[0x9] = 0x41;
				wavHeader[0xA] = 0x56;
				wavHeader[0xB] = 0x45;
				wavHeader[0xC] = 0x66;
				wavHeader[0xD] = 0x6D;
				wavHeader[0xE] = 0x74;
				wavHeader[0xF] = 0x20;
				wavHeader[0x10] = 0x10;
				wavHeader[0x11] = 0x00;
				wavHeader[0x12] = 0x00;
				wavHeader[0x13] = 0x00;
				wavHeader[0x14] = 0x01;
				wavHeader[0x15] = 0x00;
				wavHeader[0x16] = 0x01;
				wavHeader[0x17] = 0x00;
				wavHeader[0x18] = (((unsigned long)samplingRateFloat >> 0) & 0xFF);
				wavHeader[0x19] = (((unsigned long)samplingRateFloat >> 8) & 0xFF);
				wavHeader[0x1A] = (((unsigned long)samplingRateFloat >> 16) & 0xFF);
				wavHeader[0x1B] = (((unsigned long)samplingRateFloat >> 24) & 0xFF);
				wavHeader[0x1C] = ((((unsigned long)samplingRateFloat * 2) >> 0) & 0xFF);
				wavHeader[0x1D] = ((((unsigned long)samplingRateFloat * 2) >> 8) & 0xFF);
				wavHeader[0x1E] = ((((unsigned long)samplingRateFloat * 2) >> 16) & 0xFF);
				wavHeader[0x1F] = ((((unsigned long)samplingRateFloat * 2) >> 24) & 0xFF);
				wavHeader[0x20] = 0x02;
				wavHeader[0x21] = 0x00;
				wavHeader[0x22] = 0x10;
				wavHeader[0x23] = 0x00;
				wavHeader[0x24] = 0x64;
				wavHeader[0x25] = 0x61;
				wavHeader[0x26] = 0x74;
				wavHeader[0x27] = 0x61;

				fwrite(wavHeader, 1, 0x28, outFileTempRaw );

				delete [] wavHeader;

				unsigned long length = (nSamples * 2);
				fwrite(&length, 1, 4, outFileTempRaw);

				for (int x = 0; x < nSamples; x++)
				{
					fwrite(&outRawData[x], 1,2, outFileTempRaw);
				}

				if (alWave->adpcmWave->loop != NULL)
				{
					unsigned char* wavHeader = new unsigned char[0x44];
					for (int x = 0; x < 0x44; x++)
						wavHeader[x] = 0x00;

					wavHeader[0x0] = 0x73;
					wavHeader[0x1] = 0x6D;
					wavHeader[0x2] = 0x70;
					wavHeader[0x3] = 0x6C;
					wavHeader[0x4] = 0x3C;
					wavHeader[0x5] = 0x00;
					wavHeader[0x6] = 0x00;
					wavHeader[0x7] = 0x00;
					
					if (alBank->percussion->sounds[sound]->key.keybase != 0)
						wavHeader[0x14] = alBank->percussion->sounds[sound]->key.keybase;//0x3C;
					else
						wavHeader[0x14] = 0x3C;
					wavHeader[0x15] = 0x00;
					wavHeader[0x16] = 0x00;
					wavHeader[0x17] = 0x00;
					
					wavHeader[0x24] = 0x01;
					wavHeader[0x25] = 0x00;
					wavHeader[0x26] = 0x00;
					wavHeader[0x27] = 0x00;

					if (alWave->adpcmWave->loop->count > 0)
					{
						wavHeader[0x34] = ((alWave->adpcmWave->loop->start >> 0) & 0xFF);
						wavHeader[0x35] = ((alWave->adpcmWave->loop->start >> 8) & 0xFF);
						wavHeader[0x36] = ((alWave->adpcmWave->loop->start >> 16) & 0xFF);
						wavHeader[0x37] = ((alWave->adpcmWave->loop->start >> 24) & 0xFF);
						wavHeader[0x38] = (((alWave->adpcmWave->loop->end) >> 0) & 0xFF);
						wavHeader[0x39] = (((alWave->adpcmWave->loop->end) >> 8) & 0xFF);
						wavHeader[0x3A] = (((alWave->adpcmWave->loop->end) >> 16) & 0xFF);
						wavHeader[0x3B] = (((alWave->adpcmWave->loop->end) >> 24) & 0xFF);

						if (alWave->adpcmWave->loop->count == 0xFFFFFFFF)
						{
							wavHeader[0x40] = 0x00;
							wavHeader[0x41] = 0x00;
							wavHeader[0x42] = 0x00;
							wavHeader[0x43] = 0x00;
						}
						else
						{
							wavHeader[0x40] = (((alWave->adpcmWave->loop->count) >> 0) & 0xFF);
							wavHeader[0x41] = (((alWave->adpcmWave->loop->count) >> 8) & 0xFF);
							wavHeader[0x42] = (((alWave->adpcmWave->loop->count) >> 16) & 0xFF);
							wavHeader[0x43] = (((alWave->adpcmWave->loop->count) >> 24) & 0xFF);
						}
					}


					fwrite(wavHeader, 1, 0x44, outFileTempRaw );

					delete [] wavHeader;
				}
				else
				{
					unsigned char* wavHeader = new unsigned char[0x44];
					for (int x = 0; x < 0x44; x++)
						wavHeader[x] = 0x00;

					wavHeader[0x0] = 0x73;
					wavHeader[0x1] = 0x6D;
					wavHeader[0x2] = 0x70;
					wavHeader[0x3] = 0x6C;
					wavHeader[0x4] = 0x3C;
					wavHeader[0x5] = 0x00;
					wavHeader[0x6] = 0x00;
					wavHeader[0x7] = 0x00;
					
					if (alBank->percussion->sounds[sound]->key.keybase != 0)
						wavHeader[0x14] = alBank->percussion->sounds[sound]->key.keybase;//0x3C;
					else
						wavHeader[0x14] = 0x3C;
					wavHeader[0x15] = 0x00;
					wavHeader[0x16] = 0x00;
					wavHeader[0x17] = 0x00;

					fwrite(wavHeader, 1, 0x44, outFileTempRaw );

					delete [] wavHeader;
				}

				fclose(outFileTempRaw);

				delete [] outRawData;
			}
			else if (alWave->type == AL_VOX_WAVE)
			{
				CString directory = outputFile.Mid(0, (outputFile.ReverseFind('\\')+1));

				FILE* outFileTemp = fopen(directory + "tempASA3d.vox", "wb");
				if (outFileTemp == NULL)
				{
					return false;
				}
				fwrite(alBank->percussion->sounds[sound]->wav.wavData, 1, alBank->percussion->sounds[sound]->wav.len, outFileTemp);
				fflush(outFileTemp);
				fclose(outFileTemp);

				::SetCurrentDirectory(mainFolder);

				CString tempStr;
				tempStr.Format("sox -r %d -c 1 \"%s\" -e signed -t wavpcm \"%s\"", alBank->percussion->samplerate, directory + "tempASA3d.vox", outputFile);
				hiddenExec(_T(tempStr.GetBuffer()), mainFolder);
			}
			// Full credit to Musyx goes to Bobby Smiles (from Mupen emulator)
			else if (alWave->type == AL_MUSYX_WAVE)
			{
				if ((alWave->adpcmWave == NULL) || (alWave->adpcmWave->book == NULL))
					return false;

				signed short* outRawData = new signed short[alWave->len * 4];
				int nSamples = decodemusyxadpcm(alWave->wavData, outRawData, alWave->len, alWave->adpcmWave->book);
				
				nSamples = alWave->sampleRateNotInDefaultNintendoSpec;

				FILE* outFileTempRaw = fopen(outputFile, "wb");
				if (outFileTempRaw == NULL)
				{
					MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
					return false;
				}

				unsigned char* wavHeader = new unsigned char[0x28];


				wavHeader[0x0] = 0x52;
				wavHeader[0x1] = 0x49;
				wavHeader[0x2] = 0x46;
				wavHeader[0x3] = 0x46;
				unsigned long chunkSize = 0x28 + (nSamples * 2) + 0x44 - 0x8;
				wavHeader[0x4] = ((chunkSize >> 0) & 0xFF);
				wavHeader[0x5] = ((chunkSize >> 8) & 0xFF);
				wavHeader[0x6] = ((chunkSize >> 16) & 0xFF);
				wavHeader[0x7] = ((chunkSize >> 24) & 0xFF);
				wavHeader[0x8] = 0x57;
				wavHeader[0x9] = 0x41;
				wavHeader[0xA] = 0x56;
				wavHeader[0xB] = 0x45;
				wavHeader[0xC] = 0x66;
				wavHeader[0xD] = 0x6D;
				wavHeader[0xE] = 0x74;
				wavHeader[0xF] = 0x20;
				wavHeader[0x10] = 0x10;
				wavHeader[0x11] = 0x00;
				wavHeader[0x12] = 0x00;
				wavHeader[0x13] = 0x00;
				wavHeader[0x14] = 0x01;
				wavHeader[0x15] = 0x00;
				wavHeader[0x16] = 0x01;
				wavHeader[0x17] = 0x00;
				wavHeader[0x18] = (((unsigned long)samplingRateFloat >> 0) & 0xFF);
				wavHeader[0x19] = (((unsigned long)samplingRateFloat >> 8) & 0xFF);
				wavHeader[0x1A] = (((unsigned long)samplingRateFloat >> 16) & 0xFF);
				wavHeader[0x1B] = (((unsigned long)samplingRateFloat >> 24) & 0xFF);
				wavHeader[0x1C] = ((((unsigned long)samplingRateFloat * 2) >> 0) & 0xFF);
				wavHeader[0x1D] = ((((unsigned long)samplingRateFloat * 2) >> 8) & 0xFF);
				wavHeader[0x1E] = ((((unsigned long)samplingRateFloat * 2) >> 16) & 0xFF);
				wavHeader[0x1F] = ((((unsigned long)samplingRateFloat * 2) >> 24) & 0xFF);
				wavHeader[0x20] = 0x02;
				wavHeader[0x21] = 0x00;
				wavHeader[0x22] = 0x10;
				wavHeader[0x23] = 0x00;
				wavHeader[0x24] = 0x64;
				wavHeader[0x25] = 0x61;
				wavHeader[0x26] = 0x74;
				wavHeader[0x27] = 0x61;

				fwrite(wavHeader, 1, 0x28, outFileTempRaw );

				delete [] wavHeader;

				unsigned long length = (nSamples * 2);
				fwrite(&length, 1, 4, outFileTempRaw);

				for (int x = 0; x < nSamples; x++)
				{
					fwrite(&outRawData[x], 1,2, outFileTempRaw);
				}

				if (alWave->adpcmWave->loop != NULL)
				{
					unsigned char* wavHeader = new unsigned char[0x44];
					for (int x = 0; x < 0x44; x++)
						wavHeader[x] = 0x00;

					wavHeader[0x0] = 0x73;
					wavHeader[0x1] = 0x6D;
					wavHeader[0x2] = 0x70;
					wavHeader[0x3] = 0x6C;
					wavHeader[0x4] = 0x3C;
					wavHeader[0x5] = 0x00;
					wavHeader[0x6] = 0x00;
					wavHeader[0x7] = 0x00;
					
					if (alBank->percussion->sounds[sound]->key.keybase != 0)
						wavHeader[0x14] = alBank->percussion->sounds[sound]->key.keybase;//0x3C;
					else
						wavHeader[0x14] = 0x3C;
					wavHeader[0x15] = 0x00;
					wavHeader[0x16] = 0x00;
					wavHeader[0x17] = 0x00;
					
					wavHeader[0x24] = 0x01;
					wavHeader[0x25] = 0x00;
					wavHeader[0x26] = 0x00;
					wavHeader[0x27] = 0x00;

					if (alWave->adpcmWave->loop->count > 0)
					{
						wavHeader[0x34] = ((alWave->adpcmWave->loop->start >> 0) & 0xFF);
						wavHeader[0x35] = ((alWave->adpcmWave->loop->start >> 8) & 0xFF);
						wavHeader[0x36] = ((alWave->adpcmWave->loop->start >> 16) & 0xFF);
						wavHeader[0x37] = ((alWave->adpcmWave->loop->start >> 24) & 0xFF);
						wavHeader[0x38] = (((alWave->adpcmWave->loop->end) >> 0) & 0xFF);
						wavHeader[0x39] = (((alWave->adpcmWave->loop->end) >> 8) & 0xFF);
						wavHeader[0x3A] = (((alWave->adpcmWave->loop->end) >> 16) & 0xFF);
						wavHeader[0x3B] = (((alWave->adpcmWave->loop->end) >> 24) & 0xFF);

						if (alWave->adpcmWave->loop->count == 0xFFFFFFFF)
						{
							wavHeader[0x40] = 0x00;
							wavHeader[0x41] = 0x00;
							wavHeader[0x42] = 0x00;
							wavHeader[0x43] = 0x00;
						}
						else
						{
							wavHeader[0x40] = (((alWave->adpcmWave->loop->count) >> 0) & 0xFF);
							wavHeader[0x41] = (((alWave->adpcmWave->loop->count) >> 8) & 0xFF);
							wavHeader[0x42] = (((alWave->adpcmWave->loop->count) >> 16) & 0xFF);
							wavHeader[0x43] = (((alWave->adpcmWave->loop->count) >> 24) & 0xFF);
						}
					}


					fwrite(wavHeader, 1, 0x44, outFileTempRaw );

					delete [] wavHeader;
				}
				else
				{
					unsigned char* wavHeader = new unsigned char[0x44];
					for (int x = 0; x < 0x44; x++)
						wavHeader[x] = 0x00;

					wavHeader[0x0] = 0x73;
					wavHeader[0x1] = 0x6D;
					wavHeader[0x2] = 0x70;
					wavHeader[0x3] = 0x6C;
					wavHeader[0x4] = 0x3C;
					wavHeader[0x5] = 0x00;
					wavHeader[0x6] = 0x00;
					wavHeader[0x7] = 0x00;
					
					if (alBank->percussion->sounds[sound]->key.keybase != 0)
						wavHeader[0x14] = alBank->percussion->sounds[sound]->key.keybase;//0x3C;
					else
						wavHeader[0x14] = 0x3C;
					wavHeader[0x15] = 0x00;
					wavHeader[0x16] = 0x00;
					wavHeader[0x17] = 0x00;

					fwrite(wavHeader, 1, 0x44, outFileTempRaw );

					delete [] wavHeader;
				}

				fclose(outFileTempRaw);

				delete [] outRawData;
			}
			else if ((alWave->type == AL_SIGNED_RAW8) || (alWave->type == AL_SIGNED_RAW16))
			{
				int flags = (alWave->type == AL_SIGNED_RAW16);

				FILE* outFileTempRaw = fopen(outputFile, "wb");
				if (outFileTempRaw == NULL)
				{
					MessageBox(NULL, "Cannot open temporary file", "Error", NULL);
					return false;
				}

				unsigned char wavHeader[0x28];

				wavHeader[0x0] = 0x52;
				wavHeader[0x1] = 0x49;
				wavHeader[0x2] = 0x46;
				wavHeader[0x3] = 0x46;
				unsigned long chunkSize = 0x28 + alWave->len + 0x44 - 0x8;
				wavHeader[0x4] = ((chunkSize >> 0) & 0xFF);
				wavHeader[0x5] = ((chunkSize >> 8) & 0xFF);
				wavHeader[0x6] = ((chunkSize >> 16) & 0xFF);
				wavHeader[0x7] = ((chunkSize >> 24) & 0xFF);
				wavHeader[0x8] = 0x57;
				wavHeader[0x9] = 0x41;
				wavHeader[0xA] = 0x56;
				wavHeader[0xB] = 0x45;
				wavHeader[0xC] = 0x66;
				wavHeader[0xD] = 0x6D;
				wavHeader[0xE] = 0x74;
				wavHeader[0xF] = 0x20;
				wavHeader[0x10] = 0x10;
				wavHeader[0x11] = 0x00;
				wavHeader[0x12] = 0x00;
				wavHeader[0x13] = 0x00;
				wavHeader[0x14] = 0x01;
				wavHeader[0x15] = 0x00;
				wavHeader[0x16] = 0x01;
				wavHeader[0x17] = 0x00;
				wavHeader[0x18] = (((unsigned long)samplingRateFloat >> 0) & 0xFF);
				wavHeader[0x19] = (((unsigned long)samplingRateFloat >> 8) & 0xFF);
				wavHeader[0x1A] = (((unsigned long)samplingRateFloat >> 16) & 0xFF);
				wavHeader[0x1B] = (((unsigned long)samplingRateFloat >> 24) & 0xFF);
				wavHeader[0x1C] = ((((unsigned long)samplingRateFloat * (1 + (flags & 1))) >> 0) & 0xFF);
				wavHeader[0x1D] = ((((unsigned long)samplingRateFloat * (1 + (flags & 1))) >> 8) & 0xFF);
				wavHeader[0x1E] = ((((unsigned long)samplingRateFloat * (1 + (flags & 1))) >> 16) & 0xFF);
				wavHeader[0x1F] = ((((unsigned long)samplingRateFloat * (1 + (flags & 1))) >> 24) & 0xFF);
				wavHeader[0x20] = (1 + (flags & 1));
				wavHeader[0x21] = 0x00;
				wavHeader[0x22] = (((flags & 1) + 1) * 8);
				wavHeader[0x23] = 0x00;
				wavHeader[0x24] = 0x64;
				wavHeader[0x25] = 0x61;
				wavHeader[0x26] = 0x74;
				wavHeader[0x27] = 0x61;

				fwrite(wavHeader, 1, 0x28, outFileTempRaw );

				unsigned long length = alWave->len;
				fwrite(&length, 1, 4, outFileTempRaw);

				if ((flags & 1) == 1)
				{
					fwrite(&alWave->wavData, 1, alWave->len, outFileTempRaw);
				}
				else
				{
					for (int r = 0; r < alWave->len; r++)
					{
						int value = (signed char)alWave->wavData[r];
						value += 128;
						fwrite(&value, 1, 1, outFileTempRaw);

					}
				}

				fclose(outFileTempRaw);
			}

			return true;

		}
	}
	return false;
}

BOOL CN64AIFCAudio::hiddenExec (PTSTR pCmdLine, CString currentDirectory)
{
	::SetCurrentDirectory(currentDirectory);
   STARTUPINFO si;
   PROCESS_INFORMATION processInfo;
   ZeroMemory(&si, sizeof(si));
   si.cb           = sizeof(si);
   si.dwFlags      = STARTF_USESHOWWINDOW;
   si.wShowWindow  = SW_HIDE;
   ZeroMemory(&processInfo, sizeof(processInfo));


   if (currentDirectory.ReverseFind('\\') == (currentDirectory.GetLength()-1))
   {
		currentDirectory = currentDirectory.Mid(0, (currentDirectory.GetLength()-1));
   }

   /*return */CreateProcess(0, pCmdLine, 0, 0, FALSE, 0, 0, currentDirectory, &si, &processInfo);
   WaitForSingleObject(processInfo.hProcess, 20000);
   DWORD exitCode;
   if (GetExitCodeProcess(processInfo.hProcess, &exitCode))
   {
        if (exitCode == STILL_ACTIVE)
		{
			MessageBox(NULL, "For some reason Process Failed", "Error", NULL);
			TerminateProcess(processInfo.hProcess, exitCode);
			return false;
		}
   }   
   return true;
};

bool CN64AIFCAudio::AddSound(ALBank*& alBank, int instrument, CString rawWavFileName, unsigned long& samplingRate, bool type)
{
	AddSound(alBank, instrument);

	bool replace = ReplaceSoundWithWavData(alBank, instrument, (alBank->inst[instrument]->soundCount-1), rawWavFileName, samplingRate, type, PRIMARY, false);
	if (replace)
	{
		UpdateAudioOffsets(alBank);
	}
	return replace;
}
bool CN64AIFCAudio::AddSound(ALBank*& alBank, int instrument)
{
	ALSound** newSounds = new ALSound*[alBank->inst[instrument]->soundCount + 1];
	for (int x = 0; x < alBank->inst[instrument]->soundCount; x++)
	{
		newSounds[x] = alBank->inst[instrument]->sounds[x];
	}

	newSounds[alBank->inst[instrument]->soundCount] = new ALSound();
	newSounds[alBank->inst[instrument]->soundCount]->env.attackTime = 0;
	newSounds[alBank->inst[instrument]->soundCount]->env.attackVolume = 0x7F;
	newSounds[alBank->inst[instrument]->soundCount]->env.decayTime = 0xFFFFFFFF;
	newSounds[alBank->inst[instrument]->soundCount]->env.decayVolume = 0x7F;
	newSounds[alBank->inst[instrument]->soundCount]->env.releaseTime = 0;
	newSounds[alBank->inst[instrument]->soundCount]->flags = 0;
	newSounds[alBank->inst[instrument]->soundCount]->key.detune = 0;
	newSounds[alBank->inst[instrument]->soundCount]->key.keybase = 0x3C;
	newSounds[alBank->inst[instrument]->soundCount]->key.keymax = 0x7F;
	newSounds[alBank->inst[instrument]->soundCount]->key.keymin = 0;
	newSounds[alBank->inst[instrument]->soundCount]->key.velocitymax = 0x7F;
	newSounds[alBank->inst[instrument]->soundCount]->key.velocitymin = 0;
	newSounds[alBank->inst[instrument]->soundCount]->samplePan = 0x40;
	newSounds[alBank->inst[instrument]->soundCount]->sampleVolume = 0x7F;
	newSounds[alBank->inst[instrument]->soundCount]->wav.base = 0;
	newSounds[alBank->inst[instrument]->soundCount]->wav.len = 4;
	newSounds[alBank->inst[instrument]->soundCount]->wav.type = AL_RAW16_WAVE;
	newSounds[alBank->inst[instrument]->soundCount]->wav.flags = 0;
	newSounds[alBank->inst[instrument]->soundCount]->wav.wavData = new unsigned char[4];
	newSounds[alBank->inst[instrument]->soundCount]->wav.wavData[0] = 0x3;
	newSounds[alBank->inst[instrument]->soundCount]->wav.wavData[1] = 0x0;
	newSounds[alBank->inst[instrument]->soundCount]->wav.wavData[2] = 0x0;
	newSounds[alBank->inst[instrument]->soundCount]->wav.wavData[3] = 0x0;
	newSounds[alBank->inst[instrument]->soundCount]->wav.rawWave = new ALRAWWaveInfo();
	newSounds[alBank->inst[instrument]->soundCount]->wav.rawWave->loop = NULL;

	delete [] alBank->inst[instrument]->sounds;
	alBank->inst[instrument]->sounds = newSounds;

	alBank->inst[instrument]->soundCount++;

	return true;
}

bool CN64AIFCAudio::AddPercussion(ALBank*& alBank, CString rawWavFileName, unsigned long& samplingRate, bool type)
{
	AddPercussion(alBank);

	bool replace = ReplacePercussionWithWavData(alBank, (alBank->percussion->soundCount-1), rawWavFileName, samplingRate, type);
	if (replace)
	{
		UpdateAudioOffsets(alBank);
	}
	return replace;
}
bool CN64AIFCAudio::AddPercussion(ALBank*& alBank)
{
	ALSound** newSounds = new ALSound*[alBank->percussion->soundCount + 1];
	for (int x = 0; x < alBank->percussion->soundCount; x++)
	{
		newSounds[x] = alBank->percussion->sounds[x];
	}

	newSounds[alBank->percussion->soundCount] = new ALSound();
	newSounds[alBank->percussion->soundCount]->env.attackTime = 0;
	newSounds[alBank->percussion->soundCount]->env.attackVolume = 0x7F;
	newSounds[alBank->percussion->soundCount]->env.decayTime = 0xFFFFFFFF;
	newSounds[alBank->percussion->soundCount]->env.decayVolume = 0x7F;
	newSounds[alBank->percussion->soundCount]->env.releaseTime = 0;
	newSounds[alBank->percussion->soundCount]->flags = 0;
	newSounds[alBank->percussion->soundCount]->key.detune = 0;
	newSounds[alBank->percussion->soundCount]->key.keybase = 0x3C;
	newSounds[alBank->percussion->soundCount]->key.keymax = 0x7F;
	newSounds[alBank->percussion->soundCount]->key.keymin = 0;
	newSounds[alBank->percussion->soundCount]->key.velocitymax = 0x7F;
	newSounds[alBank->percussion->soundCount]->key.velocitymin = 0;
	newSounds[alBank->percussion->soundCount]->samplePan = 0x40;
	newSounds[alBank->percussion->soundCount]->sampleVolume = 0x7F;
	newSounds[alBank->percussion->soundCount]->wav.base = 0;
	newSounds[alBank->percussion->soundCount]->wav.len = 4;
	newSounds[alBank->percussion->soundCount]->wav.type = AL_RAW16_WAVE;
	newSounds[alBank->percussion->soundCount]->wav.flags = 0;
	newSounds[alBank->percussion->soundCount]->wav.wavData = new unsigned char[4];
	newSounds[alBank->percussion->soundCount]->wav.wavData[0] = 0x3;
	newSounds[alBank->percussion->soundCount]->wav.wavData[1] = 0x0;
	newSounds[alBank->percussion->soundCount]->wav.wavData[2] = 0x0;
	newSounds[alBank->percussion->soundCount]->wav.wavData[3] = 0x0;
	newSounds[alBank->percussion->soundCount]->wav.rawWave = new ALRAWWaveInfo();
	newSounds[alBank->percussion->soundCount]->wav.rawWave->loop = NULL;

	delete [] alBank->percussion->sounds;
	alBank->percussion->sounds = newSounds;

	alBank->percussion->soundCount++;

	return true;
}
void CN64AIFCAudio::DeleteSound(ALBank*& alBank, int instrument, int sound)
{
	if ((alBank->soundBankFormat != STANDARDFORMAT) && (alBank->soundBankFormat != SUPERMARIO64FORMAT)  && (alBank->soundBankFormat != N64PTRWAVETABLETABLEV2))
	{
		::MessageBox(NULL, "Cannot delete sound in this format", "Cannot delete", NULL);
		return;
	}
	ALSound** newSounds = new ALSound*[alBank->inst[instrument]->soundCount - 1];
	for (int x = 0; x < sound; x++)
	{
		newSounds[x] = alBank->inst[instrument]->sounds[x];
	}

	for (int x = (sound+1); x < alBank->inst[instrument]->soundCount; x++)
	{
		newSounds[x-1] = alBank->inst[instrument]->sounds[x];
	}

	delete [] alBank->inst[instrument]->sounds;
	alBank->inst[instrument]->sounds = newSounds;

	alBank->inst[instrument]->soundCount--;

	UpdateAudioOffsets(alBank);
}
void CN64AIFCAudio::DeletePercussion(ALBank*& alBank, int sound)
{
	if ((alBank->soundBankFormat != STANDARDFORMAT) && (alBank->soundBankFormat != SUPERMARIO64FORMAT)  && (alBank->soundBankFormat != N64PTRWAVETABLETABLEV2))
	{
		::MessageBox(NULL, "Cannot delete sound in this format", "Cannot delete", NULL);
		return;
	}
	ALSound** newSounds = new ALSound*[alBank->percussion->soundCount - 1];
	for (int x = 0; x < sound; x++)
	{
		newSounds[x] = alBank->percussion->sounds[x];
	}

	for (int x = (sound+1); x < alBank->percussion->soundCount; x++)
	{
		newSounds[x-1] = alBank->percussion->sounds[x];
	}

	delete [] alBank->percussion->sounds;
	alBank->percussion->sounds = newSounds;

	alBank->percussion->soundCount--;

	UpdateAudioOffsets(alBank);
}
void CN64AIFCAudio::MoveUpSound(ALBank*& alBank, int instrument, int sound)
{
	if (sound == 0)
		return;

	ALSound* soundAl = alBank->inst[instrument]->sounds[sound-1];
	alBank->inst[instrument]->sounds[sound-1] = alBank->inst[instrument]->sounds[sound];
	alBank->inst[instrument]->sounds[sound] = soundAl;

	UpdateAudioOffsets(alBank);
}

void CN64AIFCAudio::MoveUpPercussion(ALBank*& alBank, int sound)
{
	if (sound == 0)
		return;

	ALSound* soundAl = alBank->percussion->sounds[sound-1];
	alBank->percussion->sounds[sound-1] = alBank->percussion->sounds[sound];
	alBank->percussion->sounds[sound] = soundAl;

	UpdateAudioOffsets(alBank);
}

void CN64AIFCAudio::ExportPredictors(ALBank*& alBank, int instrument, int sound, CString fileName, byte primSel)
{
	FILE* outFile = fopen(fileName, "wb");
	if (outFile == NULL)
	{
		MessageBox(NULL, "Error opening file", "Error", NULL);
		return;
	}

	ALWave* alWave = NULL;
	if (primSel == PRIMARY)
	{
		alWave = &alBank->inst[instrument]->sounds[sound]->wav;
	}
	else if (primSel == PREVIOUS)
	{
		alWave = &alBank->inst[instrument]->sounds[sound]->wavPrevious;
	}
	else if (primSel == SECONDARY)
	{
		alWave = &alBank->inst[instrument]->sounds[sound]->wavSecondary;
	}

	unsigned long tempLong = Flip32Bit(alWave->adpcmWave->book->order);
	fwrite(&tempLong, 1, 4, outFile);

	tempLong = Flip32Bit(alWave->adpcmWave->book->npredictors);
	fwrite(&tempLong, 1, 4, outFile);

	for (int z = 0; z < (alWave->adpcmWave->book->order * alWave->adpcmWave->book->npredictors * 8); z++)
	{
		unsigned short tempShort = Flip16Bit(alWave->adpcmWave->book->predictors[z]);
		fwrite(&tempShort, 1, 2, outFile);
	}

	fclose(outFile);
}

void CN64AIFCAudio::ExportPercussionPredictors(ALBank*& alBank, int sound, CString fileName)
{
	FILE* outFile = fopen(fileName, "wb");
	if (outFile == NULL)
	{
		MessageBox(NULL, "Error opening file", "Error", NULL);
		return;
	}

	ALWave* alWave = &alBank->percussion->sounds[sound]->wav;

	unsigned long tempLong = Flip32Bit(alWave->adpcmWave->book->order);
	fwrite(&tempLong, 1, 4, outFile);

	tempLong = Flip32Bit(alWave->adpcmWave->book->npredictors);
	fwrite(&tempLong, 1, 4, outFile);

	for (int z = 0; z < (alWave->adpcmWave->book->order * alWave->adpcmWave->book->npredictors * 8); z++)
	{
		unsigned short tempShort = Flip16Bit(alWave->adpcmWave->book->predictors[z]);
		fwrite(&tempShort, 1, 2, outFile);
	}

	fclose(outFile);
}

void CN64AIFCAudio::ExportEADPercussionPredictors(ALBank*& alBank, int percussion, CString fileName)
{
	FILE* outFile = fopen(fileName, "wb");
	if (outFile == NULL)
	{
		MessageBox(NULL, "Error opening file", "Error", NULL);
		return;
	}

	ALWave* alWave = &alBank->eadPercussion[percussion].wav;

	unsigned long tempLong = Flip32Bit(alWave->adpcmWave->book->order);
	fwrite(&tempLong, 1, 4, outFile);

	tempLong = Flip32Bit(alWave->adpcmWave->book->npredictors);
	fwrite(&tempLong, 1, 4, outFile);

	for (int z = 0; z < (alWave->adpcmWave->book->order * alWave->adpcmWave->book->npredictors * 8); z++)
	{
		unsigned short tempShort = Flip16Bit(alWave->adpcmWave->book->predictors[z]);
		fwrite(&tempShort, 1, 2, outFile);
	}

	fclose(outFile);
}

void CN64AIFCAudio::ExportSfxPredictors(ALBank*& alBank, int sfx, CString fileName)
{
	FILE* outFile = fopen(fileName, "wb");
	if (outFile == NULL)
	{
		MessageBox(NULL, "Error opening file", "Error", NULL);
		return;
	}

	ALWave* alWave = alBank->alSfx[sfx];

	unsigned long tempLong = Flip32Bit(alWave->adpcmWave->book->order);
	fwrite(&tempLong, 1, 4, outFile);

	tempLong = Flip32Bit(alWave->adpcmWave->book->npredictors);
	fwrite(&tempLong, 1, 4, outFile);

	for (int z = 0; z < (alWave->adpcmWave->book->order * alWave->adpcmWave->book->npredictors * 8); z++)
	{
		unsigned short tempShort = Flip16Bit(alWave->adpcmWave->book->predictors[z]);
		fwrite(&tempShort, 1, 2, outFile);
	}

	fclose(outFile);
}

void CN64AIFCAudio::ImportPredictors(ALBank*& alBank, int instrument, int sound, CString fileName, byte primSel)
{
	int fileSize = GetSizeFile(fileName);
	FILE* inFile = fopen(fileName, "rb");
	if (inFile == NULL)
	{
		MessageBox(NULL, "Error opening", "Error", NULL);
		return;
	}

	if (fileSize < 0x8)
	{
		MessageBox(NULL, "Error too small file", "Error", NULL);
		fclose(inFile);
		return;
	}


	unsigned char* buffer = new unsigned char[fileSize];
	fread(buffer, 1, fileSize, inFile);
	fclose(inFile);
	
	ALWave* alWave = NULL;
	if (primSel == PRIMARY)
	{
		alWave = &alBank->inst[instrument]->sounds[sound]->wav;
	}
	else if (primSel == PREVIOUS)
	{
		alWave = &alBank->inst[instrument]->sounds[sound]->wavPrevious;
	}
	else if (primSel == SECONDARY)
	{
		alWave = &alBank->inst[instrument]->sounds[sound]->wavSecondary;
	}

	alWave->adpcmWave->book->order = CharArrayToLong(&buffer[0]);
	alWave->adpcmWave->book->npredictors = CharArrayToLong(&buffer[4]);

	if (fileSize != (8 + ((alWave->adpcmWave->book->order * alWave->adpcmWave->book->npredictors * 8) * 2)))
	{
		delete [] buffer;
		MessageBox(NULL, "Error invalid file size", "Error", NULL);
		return;
	}

	delete [] alWave->adpcmWave->book->predictors;
	alWave->adpcmWave->book->predictors = new signed short[(alWave->adpcmWave->book->order * alWave->adpcmWave->book->npredictors * 8)];
	
	

	for (int z = 0; z < (alWave->adpcmWave->book->order * alWave->adpcmWave->book->npredictors * 8); z++)
	{
		alWave->adpcmWave->book->predictors[z] = CharArrayToShort(&buffer[0x8 + (z * 2)]);
	}

	delete [] buffer;

	UpdateAudioOffsets(alBank);
}

void CN64AIFCAudio::ImportPercussionPredictors(ALBank*& alBank, int sound, CString fileName)
{
	int fileSize = GetSizeFile(fileName);
	FILE* inFile = fopen(fileName, "rb");
	if (inFile == NULL)
	{
		MessageBox(NULL, "Error opening", "Error", NULL);
		return;
	}

	if (fileSize < 0x8)
	{
		MessageBox(NULL, "Error too small file", "Error", NULL);
		fclose(inFile);
		return;
	}


	unsigned char* buffer = new unsigned char[fileSize];
	fread(buffer, 1, fileSize, inFile);
	fclose(inFile);
	
	ALWave* alWave = &alBank->percussion->sounds[sound]->wav;

	alWave->adpcmWave->book->order = CharArrayToLong(&buffer[0]);
	alWave->adpcmWave->book->npredictors = CharArrayToLong(&buffer[4]);

	if (fileSize != (8 + ((alWave->adpcmWave->book->order * alWave->adpcmWave->book->npredictors * 8) * 2)))
	{
		delete [] buffer;
		MessageBox(NULL, "Error invalid file size", "Error", NULL);
		return;
	}

	delete [] alWave->adpcmWave->book->predictors;
	alWave->adpcmWave->book->predictors = new signed short[(alWave->adpcmWave->book->order * alWave->adpcmWave->book->npredictors * 8)];
	
	

	for (int z = 0; z < (alWave->adpcmWave->book->order * alWave->adpcmWave->book->npredictors * 8); z++)
	{
		alWave->adpcmWave->book->predictors[z] = CharArrayToShort(&buffer[0x8 + (z * 2)]);
	}

	delete [] buffer;

	UpdateAudioOffsets(alBank);
}

void CN64AIFCAudio::ImportEADPercussionPredictors(ALBank*& alBank, int percussion, CString fileName)
{
	int fileSize = GetSizeFile(fileName);
	FILE* inFile = fopen(fileName, "rb");
	if (inFile == NULL)
	{
		MessageBox(NULL, "Error opening", "Error", NULL);
		return;
	}

	if (fileSize < 0x8)
	{
		MessageBox(NULL, "Error too small file", "Error", NULL);
		fclose(inFile);
		return;
	}


	unsigned char* buffer = new unsigned char[fileSize];
	fread(buffer, 1, fileSize, inFile);
	fclose(inFile);
	
	ALWave* alWave = &alBank->eadPercussion[percussion].wav;

	alWave->adpcmWave->book->order = CharArrayToLong(&buffer[0]);
	alWave->adpcmWave->book->npredictors = CharArrayToLong(&buffer[4]);

	if (fileSize != (8 + ((alWave->adpcmWave->book->order * alWave->adpcmWave->book->npredictors * 8) * 2)))
	{
		delete [] buffer;
		MessageBox(NULL, "Error invalid file size", "Error", NULL);
		return;
	}

	delete [] alWave->adpcmWave->book->predictors;
	alWave->adpcmWave->book->predictors = new signed short[(alWave->adpcmWave->book->order * alWave->adpcmWave->book->npredictors * 8)];
	
	

	for (int z = 0; z < (alWave->adpcmWave->book->order * alWave->adpcmWave->book->npredictors * 8); z++)
	{
		alWave->adpcmWave->book->predictors[z] = CharArrayToShort(&buffer[0x8 + (z * 2)]);
	}

	delete [] buffer;

	UpdateAudioOffsets(alBank);
}

void CN64AIFCAudio::ImportSfxPredictors(ALBank*& alBank, int sfx, CString fileName)
{
	int fileSize = GetSizeFile(fileName);
	FILE* inFile = fopen(fileName, "rb");
	if (inFile == NULL)
	{
		MessageBox(NULL, "Error opening", "Error", NULL);
		return;
	}

	if (fileSize < 0x8)
	{
		MessageBox(NULL, "Error too small file", "Error", NULL);
		fclose(inFile);
		return;
	}


	unsigned char* buffer = new unsigned char[fileSize];
	fread(buffer, 1, fileSize, inFile);
	fclose(inFile);
	
	ALWave* alWave = alBank->alSfx[sfx];

	alWave->adpcmWave->book->order = CharArrayToLong(&buffer[0]);
	alWave->adpcmWave->book->npredictors = CharArrayToLong(&buffer[4]);

	if (fileSize != (8 + ((alWave->adpcmWave->book->order * alWave->adpcmWave->book->npredictors * 8) * 2)))
	{
		delete [] buffer;
		MessageBox(NULL, "Error invalid file size", "Error", NULL);
		return;
	}

	delete [] alWave->adpcmWave->book->predictors;
	alWave->adpcmWave->book->predictors = new signed short[(alWave->adpcmWave->book->order * alWave->adpcmWave->book->npredictors * 8)];
	
	

	for (int z = 0; z < (alWave->adpcmWave->book->order * alWave->adpcmWave->book->npredictors * 8); z++)
	{
		alWave->adpcmWave->book->predictors[z] = CharArrayToShort(&buffer[0x8 + (z * 2)]);
	}

	delete [] buffer;

	UpdateAudioOffsets(alBank);
}

void CN64AIFCAudio::UpdateAudioOffsets(ALBank*& alBank)
{
	unsigned char* ctl = NULL;
	unsigned char* tbl = NULL;
	int ctlCounter, tblCounter;
	// update base offsets
	if (alBank->soundBankFormat == STANDARDFORMAT)
	{
		WriteAudio(alBank, ctl, ctlCounter, tbl, tblCounter);
	}
	else if (alBank->soundBankFormat == SUPERMARIO64FORMAT)
	{
		//WriteAudioSuperMario(alBank, ctl, ctlCounter, tbl, tblCounter);
	}
	else if (alBank->soundBankFormat == N64PTRWAVETABLETABLEV2)
	{
		WriteAudioN64PtrWavetableV2(alBank, ctl, ctlCounter, tbl, tblCounter);
	}
	else if (alBank->soundBankFormat == N64PTRWAVETABLETABLEV2BLITZ)
	{
		WriteAudioN64PtrWavetableV2Blitz("", alBank, ctl, ctlCounter, tbl, tblCounter);
	}
	else if (alBank->soundBankFormat == N64PTRWAVETABLETABLEV1)
	{
		WriteAudioN64PtrWavetableV1(alBank, ctl, ctlCounter, tbl, tblCounter);
	}
	if (ctl != NULL)
		delete [] ctl;
	if (tbl != NULL)
		delete [] tbl;
}

void CN64AIFCAudio::ExportRawData(ALBank*& alBank, int instrument, int sound, CString fileName, byte primSel)
{
	FILE* outFile = fopen(fileName, "wb");
	if (outFile == NULL)
	{
		MessageBox(NULL, "Error opening file", "Error", NULL);
		return;
	}

	ALWave* alWave = NULL;
	if (primSel == PRIMARY)
	{
		alWave = &alBank->inst[instrument]->sounds[sound]->wav;
	}
	else if (primSel == PREVIOUS)
	{
		alWave = &alBank->inst[instrument]->sounds[sound]->wavPrevious;
	}
	else if (primSel == SECONDARY)
	{
		alWave = &alBank->inst[instrument]->sounds[sound]->wavSecondary;
	}

	fwrite(alWave->wavData, 1, alWave->len, outFile);

	fclose(outFile);
}

void CN64AIFCAudio::ImportRawData(ALBank*& alBank, int instrument, int sound, CString fileName, byte primSel)
{
	int fileSize = GetSizeFile(fileName);
	FILE* inFile = fopen(fileName, "rb");
	if (inFile == NULL)
	{
		MessageBox(NULL, "Error opening", "Error", NULL);
		return;
	}

	ALWave* alWave = NULL;
	if (primSel == PRIMARY)
	{
		alWave = &alBank->inst[instrument]->sounds[sound]->wav;
	}
	else if (primSel == PREVIOUS)
	{
		alWave = &alBank->inst[instrument]->sounds[sound]->wavPrevious;
	}
	else if (primSel == SECONDARY)
	{
		alWave = &alBank->inst[instrument]->sounds[sound]->wavSecondary;
	}

	alWave->len = fileSize;
	delete [] alWave->wavData;

	alWave->wavData = new unsigned char[fileSize];
	fread(alWave->wavData, 1, fileSize, inFile);
	fclose(inFile);

	if (alBank->soundBankFormat == SUPERMARIO64FORMAT)
	{
		alWave->adpcmWave->loop->start = 0;
		alWave->adpcmWave->loop->end = (fileSize * 7) / 4;
		alWave->adpcmWave->loop->count = 0;
	}

	UpdateAudioOffsets(alBank);
}


void CN64AIFCAudio::ExportPercussionRawData(ALBank*& alBank, int sound, CString fileName)
{
	FILE* outFile = fopen(fileName, "wb");
	if (outFile == NULL)
	{
		MessageBox(NULL, "Error opening file", "Error", NULL);
		return;
	}

	ALWave* alWave = &alBank->percussion->sounds[sound]->wav;

	fwrite(alWave->wavData, 1, alWave->len, outFile);

	fclose(outFile);
}

void CN64AIFCAudio::ImportPercussionRawData(ALBank*& alBank, int sound, CString fileName)
{
	int fileSize = GetSizeFile(fileName);
	FILE* inFile = fopen(fileName, "rb");
	if (inFile == NULL)
	{
		MessageBox(NULL, "Error opening", "Error", NULL);
		return;
	}

	ALWave* alWave = &alBank->percussion->sounds[sound]->wav;

	alWave->len = fileSize;
	delete [] alWave->wavData;

	alWave->wavData = new unsigned char[fileSize];
	fread(alWave->wavData, 1, fileSize, inFile);
	fclose(inFile);

	if (alBank->soundBankFormat == SUPERMARIO64FORMAT)
	{
		alWave->adpcmWave->loop->start = 0;
		alWave->adpcmWave->loop->end = (fileSize * 7) / 4;
		alWave->adpcmWave->loop->count = 0;
	}

	UpdateAudioOffsets(alBank);
}

void CN64AIFCAudio::ExportEADRawPercussionData(ALBank*& alBank, int sound, CString fileName)
{
	FILE* outFile = fopen(fileName, "wb");
	if (outFile == NULL)
	{
		MessageBox(NULL, "Error opening file", "Error", NULL);
		return;
	}

	ALWave* alWave = &alBank->eadPercussion[sound].wav;

	fwrite(alWave->wavData, 1, alWave->len, outFile);

	fclose(outFile);
}

void CN64AIFCAudio::ImportEADRawPercussionData(ALBank*& alBank, int sound, CString fileName)
{
	int fileSize = GetSizeFile(fileName);
	FILE* inFile = fopen(fileName, "rb");
	if (inFile == NULL)
	{
		MessageBox(NULL, "Error opening", "Error", NULL);
		return;
	}

	ALWave* alWave = &alBank->eadPercussion[sound].wav;
	
	alWave->len = fileSize;
	delete [] alWave->wavData;

	alWave->wavData = new unsigned char[fileSize];
	fread(alWave->wavData, 1, fileSize, inFile);
	fclose(inFile);

	if (alBank->soundBankFormat == SUPERMARIO64FORMAT)
	{
		alWave->adpcmWave->loop->start = 0;
		alWave->adpcmWave->loop->end = (fileSize * 7) / 4;
		alWave->adpcmWave->loop->count = 0;
	}

	UpdateAudioOffsets(alBank);
}

void CN64AIFCAudio::ExportRawSfxData(ALBank*& alBank, int sound, CString fileName)
{
	ALWave* alWave = alBank->alSfx[sound];

	if (alWave != NULL)
	{

		FILE* outFile = fopen(fileName, "wb");
		if (outFile == NULL)
		{
			MessageBox(NULL, "Error opening file", "Error", NULL);
			return;
		}

		fwrite(alWave->wavData, 1, alWave->len, outFile);

		fclose(outFile);
	}
	else
	{
		MessageBox(NULL, "Nothing to export", "Error", NULL);
		return;
	}
}

void CN64AIFCAudio::ImportRawSfxData(ALBank*& alBank, int sound, CString fileName)
{
	int fileSize = GetSizeFile(fileName);
	FILE* inFile = fopen(fileName, "rb");
	if (inFile == NULL)
	{
		MessageBox(NULL, "Error opening", "Error", NULL);
		return;
	}

	ALWave* alWave = alBank->alSfx[sound];
	
	alWave->len = fileSize;
	delete [] alWave->wavData;

	alWave->wavData = new unsigned char[fileSize];
	fread(alWave->wavData, 1, fileSize, inFile);
	fclose(inFile);

	UpdateAudioOffsets(alBank);
}

void CN64AIFCAudio::MoveDownSound(ALBank*& alBank, int instrument, int sound)
{
	if (sound == (alBank->inst[instrument]->soundCount-1))
		return;

	ALSound* soundAl = alBank->inst[instrument]->sounds[sound+1];
	alBank->inst[instrument]->sounds[sound+1] = alBank->inst[instrument]->sounds[sound];
	alBank->inst[instrument]->sounds[sound] = soundAl;

	UpdateAudioOffsets(alBank);
}

void CN64AIFCAudio::MoveDownPercussion(ALBank*& alBank, int sound)
{
	if (sound == (alBank->percussion->soundCount-1))
		return;

	ALSound* soundAl = alBank->percussion->sounds[sound+1];
	alBank->percussion->sounds[sound+1] = alBank->percussion->sounds[sound];
	alBank->percussion->sounds[sound] = soundAl;

	UpdateAudioOffsets(alBank);
}

bool CN64AIFCAudio::ReadWavData(CString rawWavFileName, unsigned char*& rawData, int& rawLength, unsigned long& samplingRate, bool& hasLoopData, unsigned char& keyBase, unsigned long& loopStart, unsigned long& loopEnd, unsigned long& loopCount)
{
	FILE* inWavFile = fopen(rawWavFileName, "rb");
	if (inWavFile == NULL)
	{
		MessageBox(NULL, "Error cannot read wav file", "Error", NULL);
		return false;
	}

	fseek(inWavFile, 0, SEEK_END);
	int fileSize = ftell(inWavFile);
	rewind(inWavFile);

	unsigned char* wavData = new unsigned char[fileSize];
	fread(wavData, 1, fileSize, inWavFile);
	fclose(inWavFile);

	if (((((((wavData[0] << 8) | wavData[1]) << 8) | wavData[2]) << 8) | wavData[3]) != 0x52494646)
	{
		MessageBox(NULL, "Error not RIFF wav", "Error", NULL);
		return false;
	}

	if (((((((wavData[0x8] << 8) | wavData[0x9]) << 8) | wavData[0xA]) << 8) | wavData[0xB]) != 0x57415645)
	{
		MessageBox(NULL, "Error not WAVE wav", "Error", NULL);
		return false;
	}

	bool endFlag = false;

	unsigned long currentOffset = 0xC;

	unsigned short channels = 0;
	samplingRate = 0;
	unsigned short bitRate = 0;

	bool returnFlag = false;

	while (!endFlag)
	{
		if (currentOffset >= (fileSize - 8))
			break;

		unsigned long sectionType = ((((((wavData[currentOffset] << 8) | wavData[currentOffset + 1]) << 8) | wavData[currentOffset + 2]) << 8) | wavData[currentOffset + 3]);

		if (sectionType == 0x666D7420) // fmt
		{
			unsigned long chunkSize = ((((((wavData[currentOffset + 0x7] << 8) | wavData[currentOffset + 0x6]) << 8) | wavData[currentOffset + 0x5]) << 8) | wavData[currentOffset + 0x4]);

			channels = ((wavData[currentOffset + 0xB] << 8) | wavData[currentOffset + 0xA]);

			if (channels != 0x0001)
			{
				MessageBox(NULL, "Warning: Only mono wav supported", "Error", NULL);
				endFlag = true;
				returnFlag = false;
			}

			samplingRate = ((((((wavData[currentOffset + 0xF] << 8) | wavData[currentOffset + 0xE]) << 8) | wavData[currentOffset + 0xD]) << 8) | wavData[currentOffset + 0xC]);
			
			bitRate = ((wavData[currentOffset + 0x17] << 8) | wavData[currentOffset + 0x16]);

			currentOffset += chunkSize + 8;
		}
		else if (sectionType == 0x64617461) // data
		{
			rawLength = ((((((wavData[currentOffset + 0x7] << 8) | wavData[currentOffset + 0x6]) << 8) | wavData[currentOffset + 0x5]) << 8) | wavData[currentOffset + 0x4]);

			if ((channels == 0) || (samplingRate == 0) || (bitRate == 0))
			{
				MessageBox(NULL, "Incorrect section type (missing fmt)", "Error unknown wav format", NULL);
				endFlag = true;
				returnFlag = false;
			}

			if (bitRate == 0x0010)
			{
				rawData = new unsigned char[rawLength];
				for (int x = 0; x < rawLength; x++)
				{
					rawData[x] = wavData[currentOffset + 0x8 + x];
				}
			
				returnFlag = true;
			}
			else
			{
				MessageBox(NULL, "Error only 16-bit PCM wav supported", "Error", NULL);
				endFlag = true;
				returnFlag = false;
			}

			currentOffset += rawLength + 8;
		}
		else if (sectionType == 0x736D706C) // smpl
		{
			unsigned long chunkSize = ((((((wavData[currentOffset + 0x7] << 8) | wavData[currentOffset + 0x6]) << 8) | wavData[currentOffset + 0x5]) << 8) | wavData[currentOffset + 0x4]);

			unsigned long numSampleBlocks = Flip32Bit(CharArrayToLong(&wavData[currentOffset+0x24]));
			if (numSampleBlocks > 0)
			{
				hasLoopData = true;

				keyBase = Flip32Bit(CharArrayToLong(&wavData[currentOffset+0x14])) & 0xFF;
				loopStart = Flip32Bit(CharArrayToLong(&wavData[currentOffset+0x34]));
				loopEnd = Flip32Bit(CharArrayToLong(&wavData[currentOffset+0x38]));
				loopCount = Flip32Bit(CharArrayToLong(&wavData[currentOffset+0x40]));
				if (loopCount == 0)
					loopCount = 0xFFFFFFFF;
			}

			currentOffset += 8 + chunkSize;
		}
		else
		{
			unsigned long chunkSize = ((((((wavData[currentOffset + 0x7] << 8) | wavData[currentOffset + 0x6]) << 8) | wavData[currentOffset + 0x5]) << 8) | wavData[currentOffset + 0x4]);

			currentOffset += 8 + chunkSize;
		}
	}

	delete [] wavData;
	return returnFlag;
}

bool CN64AIFCAudio::ReplaceSoundWithWavData(ALBank*& alBank, int instrument, int sound, CString rawWavFileName, unsigned long& samplingRate, bool newType, byte primSel, bool decode8Only)
{
	unsigned char* wavPCMData;
	int rawLength;

	if (alBank->inst[instrument]->sounds[sound] == NULL)
		return false;

	bool hasLoopData = false;
	unsigned char keyBase = 0x3C;
	unsigned long loopStart = 0x00000000;
	unsigned long loopEnd = 0x00000000;
	unsigned long loopCount = 0x00000000;

	if (!ReadWavData(rawWavFileName, wavPCMData, rawLength, samplingRate, hasLoopData, keyBase, loopStart, loopEnd, loopCount))
	{
		return false;
	}

	ALWave* alWave = NULL;
	if (primSel == PRIMARY)
	{
		alWave = &alBank->inst[instrument]->sounds[sound]->wav;
	}
	else if (primSel == PREVIOUS)
	{
		alWave = &alBank->inst[instrument]->sounds[sound]->wavPrevious;
	}
	else if (primSel == SECONDARY)
	{
		alWave = &alBank->inst[instrument]->sounds[sound]->wavSecondary;
	}

	if (alWave->type == AL_ADPCM_WAVE)
	{
		if (alWave->adpcmWave->loop != NULL)
		{
			delete alWave->adpcmWave->loop;
			alWave->adpcmWave->loop = NULL;
		}

		if (alWave->adpcmWave->book != NULL)
		{
			if (alWave->adpcmWave->book->predictors != NULL)
			{
				delete [] alWave->adpcmWave->book->predictors;
				alWave->adpcmWave->book->predictors = NULL;
			}
			delete alWave->adpcmWave->book;
			alWave->adpcmWave->book = NULL;
		}

		delete alWave->adpcmWave->book;
		delete alWave->adpcmWave;
		alWave->adpcmWave = NULL;
		alWave->rawWave = NULL;
	}
	else if (alWave->type == AL_RAW16_WAVE)
	{
		if (alWave->rawWave->loop != NULL)
		{
			delete alWave->rawWave->loop;
			alWave->rawWave->loop = NULL;
		}
		delete alWave->rawWave;
		alWave->rawWave = NULL;
		alWave->adpcmWave = NULL;
	}

	if (newType == AL_RAW16_WAVE)
	{
		alWave->decode8Only = false;

		alWave->type = AL_RAW16_WAVE;
		alWave->rawWave = new ALRAWWaveInfo();
		alWave->rawWave->loop = NULL;/*new ALRawLoop();
		alWave->rawWave->loop->start = 0;
		alWave->rawWave->loop->end = (rawLength-2);
		alWave->rawWave->loop->count = 0;*/

		delete [] alWave->wavData;
		alWave->wavData = new unsigned char[rawLength + 2];
		alWave->wavData[0] = 0x03;
		alWave->wavData[rawLength + 1] = 0x00;
		memcpy(&alWave->wavData[1], wavPCMData, rawLength);
		alWave->len = rawLength + 2;

		alBank->inst[instrument]->sounds[sound]->flags = 0;
		/*alBank->inst[instrument]->sounds[sound]->env.attackTime = 0;
		alBank->inst[instrument]->sounds[sound]->env.attackVolume = 0x7F;
		alBank->inst[instrument]->sounds[sound]->env.decayTime = 0xFFFFFFFF;
		alBank->inst[instrument]->sounds[sound]->env.decayVolume = 0x7F;
		alBank->inst[instrument]->sounds[sound]->env.releaseTime = 0;
		
		alBank->inst[instrument]->sounds[sound]->key.detune = 0;*/
		if (hasLoopData)
			alBank->inst[instrument]->sounds[sound]->key.keybase = keyBase;
		/*else
			alBank->inst[instrument]->sounds[sound]->key.keybase = 0x3C;
		alBank->inst[instrument]->sounds[sound]->key.keymax = 0x7F;
		alBank->inst[instrument]->sounds[sound]->key.keymin = 0;
		alBank->inst[instrument]->sounds[sound]->key.velocitymax = 0x7F;
		alBank->inst[instrument]->sounds[sound]->key.velocitymin = 0;
		alBank->inst[instrument]->sounds[sound]->samplePan = 0x40;
		alBank->inst[instrument]->sounds[sound]->sampleVolume = 0x7F;*/
		alWave->flags = 0;

		if (hasLoopData)
		{
			alWave->rawWave->loop = new ALRawLoop();
			alWave->rawWave->loop->count = loopCount;
			alWave->rawWave->loop->start = loopStart;
			alWave->rawWave->loop->end = loopEnd;
		}
	}
	else
	{
		alWave->decode8Only = decode8Only;

		alWave->type = AL_ADPCM_WAVE;
		alWave->adpcmWave = new ALADPCMWaveInfo();
		alWave->adpcmWave->loop = NULL;/*new ALRawLoop();
		alWave->rawWave->loop->start = 0;
		alWave->rawWave->loop->end = (rawLength-2);
		alWave->rawWave->loop->count = 0;*/

		alWave->adpcmWave->book = new ALADPCMBook();

		int numberSamples = (rawLength / 2);
		signed short* pcmSamples = new signed short[numberSamples];

		for (int x = 0; x < numberSamples; x++)
		{
			pcmSamples[x] = (signed short)(((wavPCMData[x*2+1] << 8)) | wavPCMData[x*2]);
		}

		if (decode8Only)
		{
			alWave->adpcmWave->book->predictors = new signed short[0x10];
			for (int x = 0; x < 0x10; x++)
				alWave->adpcmWave->book->predictors[x] = 0x00;

			alWave->adpcmWave->book->npredictors = 1;
			alWave->adpcmWave->book->order = 2;
		}
		else
		{
			alWave->adpcmWave->book->predictors = determineBestPredictors(alBank, alWave->adpcmWave->book->npredictors, alWave->adpcmWave->book->order, pcmSamples, numberSamples);
		}

		delete [] alWave->wavData;

		unsigned long vadpcmOutputLength;
		unsigned char* vadpcmData = new unsigned char[numberSamples];

		if (decode8Only)
		{
			encode_half(pcmSamples, numberSamples, vadpcmData, vadpcmOutputLength, alWave->adpcmWave->book);
		}
		else
		{
			encode(pcmSamples, numberSamples, vadpcmData, vadpcmOutputLength, alWave->adpcmWave->book);
		}

		alWave->wavData = new unsigned char[vadpcmOutputLength];
		memcpy(alWave->wavData, vadpcmData, vadpcmOutputLength);
		alWave->len = vadpcmOutputLength;

		if (alBank->soundBankFormat == SUPERMARIO64FORMAT)
		{
			alWave->adpcmWave->loop = new ALADPCMloop();
			alWave->adpcmWave->loop->start = 0;
			alWave->adpcmWave->loop->end = ((vadpcmOutputLength * 7) / 4);
			alWave->adpcmWave->loop->count = 0;

			if (hasLoopData)
			{
				if (primSel == PRIMARY)
				{
					alBank->inst[instrument]->sounds[sound]->floatKeyBase = *reinterpret_cast<unsigned long*> (&CN64AIFCAudio::keyTable[keyBase]);
				}
				else if (primSel == PREVIOUS)
				{
					alBank->inst[instrument]->sounds[sound]->floatKeyBasePrev = *reinterpret_cast<unsigned long*> (&CN64AIFCAudio::keyTable[keyBase]);
				}
				else if (primSel == SECONDARY)
				{
					alBank->inst[instrument]->sounds[sound]->floatKeyBaseSec = *reinterpret_cast<unsigned long*> (&CN64AIFCAudio::keyTable[keyBase]);
				}
			}
		}
		else
		{
			alBank->inst[instrument]->sounds[sound]->flags = 0;
			/*alBank->inst[instrument]->sounds[sound]->env.attackTime = 0;
			alBank->inst[instrument]->sounds[sound]->env.attackVolume = 0x7F;
			alBank->inst[instrument]->sounds[sound]->env.decayTime = 0xFFFFFFFF;
			alBank->inst[instrument]->sounds[sound]->env.decayVolume = 0x7F;
			alBank->inst[instrument]->sounds[sound]->env.releaseTime = 0;
			alBank->inst[instrument]->sounds[sound]->key.detune = 0;*/
			if (hasLoopData)
				alBank->inst[instrument]->sounds[sound]->key.keybase = keyBase;
			/*else
				alBank->inst[instrument]->sounds[sound]->key.keybase = 0x3C;
			alBank->inst[instrument]->sounds[sound]->key.keymax = 0x7F;
			alBank->inst[instrument]->sounds[sound]->key.keymin = 0;
			alBank->inst[instrument]->sounds[sound]->key.velocitymax = 0x7F;
			alBank->inst[instrument]->sounds[sound]->key.velocitymin = 0;
			alBank->inst[instrument]->sounds[sound]->samplePan = 0x40;
			alBank->inst[instrument]->sounds[sound]->sampleVolume = 0x7F;*/
			alWave->flags = 0;

			if (hasLoopData)
			{
				alWave->adpcmWave->loop = new ALADPCMloop();
				alWave->adpcmWave->loop->count = loopCount;
				alWave->adpcmWave->loop->start = loopStart;
				alWave->adpcmWave->loop->end = loopEnd;
				alWave->adpcmWave->loop->unknown1 = 0;
				for (int x = 0; x < 0x10; x++)
					alWave->adpcmWave->loop->state[x] = alWave->adpcmWave->book->predictors[x];

			}
		}

		delete [] pcmSamples;
		delete [] vadpcmData;
	}

	delete [] wavPCMData;

	UpdateAudioOffsets(alBank);

	return true;
}

bool CN64AIFCAudio::ReplacePercussionWithWavData(ALBank*& alBank, int sound, CString rawWavFileName, unsigned long& samplingRate, bool newType)
{
	unsigned char* wavPCMData;
	int rawLength;

	if (alBank->percussion == NULL)
		return false;

	bool hasLoopData = false;
	unsigned char keyBase = 0x3C;
	unsigned long loopStart = 0x00000000;
	unsigned long loopEnd = 0x00000000;
	unsigned long loopCount = 0x00000000;

	if (!ReadWavData(rawWavFileName, wavPCMData, rawLength, samplingRate, hasLoopData, keyBase, loopStart, loopEnd, loopCount))
	{
		return false;
	}

	ALWave* alWave = &alBank->percussion->sounds[sound]->wav;

	if (alWave->type == AL_ADPCM_WAVE)
	{
		if (alWave->adpcmWave->loop != NULL)
		{
			delete alWave->adpcmWave->loop;
			alWave->adpcmWave->loop = NULL;
		}

		if (alWave->adpcmWave->book != NULL)
		{
			if (alWave->adpcmWave->book->predictors != NULL)
			{
				delete [] alWave->adpcmWave->book->predictors;
				alWave->adpcmWave->book->predictors = NULL;
			}
			delete alWave->adpcmWave->book;
			alWave->adpcmWave->book = NULL;
		}

		delete alWave->adpcmWave->book;
		delete alWave->adpcmWave;
		alWave->adpcmWave = NULL;
		alWave->rawWave = NULL;
	}
	else if (alWave->type == AL_RAW16_WAVE)
	{
		if (alWave->rawWave->loop != NULL)
		{
			delete alWave->rawWave->loop;
			alWave->rawWave->loop = NULL;
		}
		delete alWave->rawWave;
		alWave->rawWave = NULL;
		alWave->adpcmWave = NULL;
	}

	if (newType == AL_RAW16_WAVE)
	{
		alWave->type = AL_RAW16_WAVE;
		alWave->rawWave = new ALRAWWaveInfo();
		alWave->rawWave->loop = NULL;/*new ALRawLoop();
		alWave->rawWave->loop->start = 0;
		alWave->rawWave->loop->end = (rawLength-2);
		alWave->rawWave->loop->count = 0;*/

		delete [] alWave->wavData;
		alWave->wavData = new unsigned char[rawLength + 2];
		alWave->wavData[0] = 0x03;
		alWave->wavData[rawLength + 1] = 0x00;
		memcpy(&alWave->wavData[1], wavPCMData, rawLength);
		alWave->len = rawLength + 2;

		alBank->percussion->sounds[sound]->flags = 0;
		/*alBank->percussion->sounds[sound]->env.attackTime = 0;
		alBank->percussion->sounds[sound]->env.attackVolume = 0x7F;
		alBank->percussion->sounds[sound]->env.decayTime = 0xFFFFFFFF;
		alBank->percussion->sounds[sound]->env.decayVolume = 0x7F;
		alBank->percussion->sounds[sound]->env.releaseTime = 0;
		
		alBank->percussion->sounds[sound]->key.detune = 0;*/
		if (hasLoopData)
			alBank->percussion->sounds[sound]->key.keybase = keyBase;
		/*else
			alBank->percussion->sounds[sound]->key.keybase = 0x3C;
		alBank->percussion->sounds[sound]->key.keymax = 0x7F;
		alBank->percussion->sounds[sound]->key.keymin = 0;
		alBank->percussion->sounds[sound]->key.velocitymax = 0x7F;
		alBank->percussion->sounds[sound]->key.velocitymin = 0;
		alBank->percussion->sounds[sound]->samplePan = 0x40;
		alBank->percussion->sounds[sound]->sampleVolume = 0x7F;*/
		alWave->flags = 0;

		if (hasLoopData)
		{
			alWave->rawWave->loop = new ALRawLoop();
			alWave->rawWave->loop->count = loopCount;
			alWave->rawWave->loop->start = loopStart;
			alWave->rawWave->loop->end = loopEnd;
		}
	}
	else
	{
		alWave->type = AL_ADPCM_WAVE;
		alWave->adpcmWave = new ALADPCMWaveInfo();
		alWave->adpcmWave->loop = NULL;/*new ALRawLoop();
		alWave->rawWave->loop->start = 0;
		alWave->rawWave->loop->end = (rawLength-2);
		alWave->rawWave->loop->count = 0;*/

		alWave->adpcmWave->book = new ALADPCMBook();

		int numberSamples = (rawLength / 2);
		signed short* pcmSamples = new signed short[numberSamples];

		for (int x = 0; x < numberSamples; x++)
		{
			pcmSamples[x] = (signed short)(((wavPCMData[x*2+1] << 8)) | wavPCMData[x*2]);
		}

		alWave->adpcmWave->book->predictors = determineBestPredictors(alBank, alWave->adpcmWave->book->npredictors, alWave->adpcmWave->book->order, pcmSamples, numberSamples);

		delete [] alWave->wavData;

		unsigned long vadpcmOutputLength;
		unsigned char* vadpcmData = new unsigned char[numberSamples];

		encode(pcmSamples, numberSamples, vadpcmData, vadpcmOutputLength, alWave->adpcmWave->book);

		alWave->wavData = new unsigned char[vadpcmOutputLength];
		memcpy(alWave->wavData, vadpcmData, vadpcmOutputLength);
		alWave->len = vadpcmOutputLength;

		alBank->percussion->sounds[sound]->flags = 0;
		/*alBank->percussion->sounds[sound]->env.attackTime = 0;
		alBank->percussion->sounds[sound]->env.attackVolume = 0x7F;
		alBank->percussion->sounds[sound]->env.decayTime = 0xFFFFFFFF;
		alBank->percussion->sounds[sound]->env.decayVolume = 0x7F;
		alBank->percussion->sounds[sound]->env.releaseTime = 0;
		alBank->percussion->sounds[sound]->key.detune = 0;*/
		if (hasLoopData)
			alBank->percussion->sounds[sound]->key.keybase = keyBase;
		/*else
			alBank->percussion->sounds[sound]->key.keybase = 0x3C;
		alBank->percussion->sounds[sound]->key.keymax = 0x7F;
		alBank->percussion->sounds[sound]->key.keymin = 0;
		alBank->percussion->sounds[sound]->key.velocitymax = 0x7F;
		alBank->percussion->sounds[sound]->key.velocitymin = 0;
		alBank->percussion->sounds[sound]->samplePan = 0x40;
		alBank->percussion->sounds[sound]->sampleVolume = 0x7F;*/
		alWave->flags = 0;

		if (hasLoopData)
		{
			alWave->adpcmWave->loop = new ALADPCMloop();
			alWave->adpcmWave->loop->count = loopCount;
			alWave->adpcmWave->loop->start = loopStart;
			alWave->adpcmWave->loop->end = loopEnd;
			alWave->adpcmWave->loop->unknown1 = 0;
			for (int x = 0; x < 0x10; x++)
				alWave->adpcmWave->loop->state[x] = alWave->adpcmWave->book->predictors[x];

		}

		delete [] pcmSamples;
		delete [] vadpcmData;
	}

	delete [] wavPCMData;

	UpdateAudioOffsets(alBank);

	return true;
}

bool CN64AIFCAudio::ReplaceEADPercussionWithWavData(ALBank*& alBank, int percussion, CString rawWavFileName, unsigned long& samplingRate, bool newType)
{
	unsigned char* wavPCMData;
	int rawLength;

	if (alBank->eadPercussion == NULL)
		return false;

	bool hasLoopData = false;
	unsigned char keyBase = 0x3C;
	unsigned long loopStart = 0x00000000;
	unsigned long loopEnd = 0x00000000;
	unsigned long loopCount = 0x00000000;

	if (!ReadWavData(rawWavFileName, wavPCMData, rawLength, samplingRate, hasLoopData, keyBase, loopStart, loopEnd, loopCount))
	{
		return false;
	}

	ALWave* alWave = NULL;
	alWave = &alBank->eadPercussion[percussion].wav;

	if (alWave->type == AL_ADPCM_WAVE)
	{
		if (alWave->adpcmWave->loop != NULL)
		{
			delete alWave->adpcmWave->loop;
			alWave->adpcmWave->loop = NULL;
		}

		if (alWave->adpcmWave->book != NULL)
		{
			if (alWave->adpcmWave->book->predictors != NULL)
			{
				delete [] alWave->adpcmWave->book->predictors;
				alWave->adpcmWave->book->predictors = NULL;
			}
			delete alWave->adpcmWave->book;
			alWave->adpcmWave->book = NULL;
		}

		delete alWave->adpcmWave->book;
		delete alWave->adpcmWave;
		alWave->adpcmWave = NULL;
		alWave->rawWave = NULL;
	}
	else if (alWave->type == AL_RAW16_WAVE)
	{
		if (alWave->rawWave->loop != NULL)
		{
			delete alWave->rawWave->loop;
			alWave->rawWave->loop = NULL;
		}
		delete alWave->rawWave;
		alWave->rawWave = NULL;
		alWave->adpcmWave = NULL;
	}

	if (newType == AL_RAW16_WAVE)
	{
		alWave->type = AL_RAW16_WAVE;
		alWave->rawWave = new ALRAWWaveInfo();
		alWave->rawWave->loop = NULL;/*new ALRawLoop();
		alWave->rawWave->loop->start = 0;
		alWave->rawWave->loop->end = (rawLength-2);
		alWave->rawWave->loop->count = 0;*/

		delete [] alWave->wavData;
		alWave->wavData = new unsigned char[rawLength + 2];
		alWave->wavData[0] = 0x03;
		alWave->wavData[rawLength + 1] = 0x00;
		memcpy(&alWave->wavData[1], wavPCMData, rawLength);
		alWave->len = rawLength + 2;

		alWave->flags = 0;

		if (hasLoopData)
		{
			alWave->rawWave->loop = new ALRawLoop();
			alWave->rawWave->loop->count = loopCount;
			alWave->rawWave->loop->start = loopStart;
			alWave->rawWave->loop->end = loopEnd;
		}
	}
	else
	{
		alWave->type = AL_ADPCM_WAVE;
		alWave->adpcmWave = new ALADPCMWaveInfo();
		alWave->adpcmWave->loop = NULL;/*new ALRawLoop();
		alWave->rawWave->loop->start = 0;
		alWave->rawWave->loop->end = (rawLength-2);
		alWave->rawWave->loop->count = 0;*/

		alWave->adpcmWave->book = new ALADPCMBook();

		int numberSamples = (rawLength / 2);
		signed short* pcmSamples = new signed short[numberSamples];

		for (int x = 0; x < numberSamples; x++)
		{
			pcmSamples[x] = (signed short)(((wavPCMData[x*2+1] << 8)) | wavPCMData[x*2]);
		}

		alWave->adpcmWave->book->predictors = determineBestPredictors(alBank, alWave->adpcmWave->book->npredictors, alWave->adpcmWave->book->order, pcmSamples, numberSamples);

		delete [] alWave->wavData;

		unsigned long vadpcmOutputLength;
		unsigned char* vadpcmData = new unsigned char[numberSamples];

		encode(pcmSamples, numberSamples, vadpcmData, vadpcmOutputLength, alWave->adpcmWave->book);

		alWave->wavData = new unsigned char[vadpcmOutputLength];
		memcpy(alWave->wavData, vadpcmData, vadpcmOutputLength);
		alWave->len = vadpcmOutputLength;

		if ((alBank->soundBankFormat == SUPERMARIO64FORMAT)
				|| (alBank->soundBankFormat == MARIOKART64FORMAT)
				|| (alBank->soundBankFormat == ZELDAFORMAT)
				|| (alBank->soundBankFormat == STARFOX64FORMAT)
				|| (alBank->soundBankFormat == FZEROFORMAT))
		{
			alWave->adpcmWave->loop = new ALADPCMloop();
			alWave->adpcmWave->loop->start = 0;
			alWave->adpcmWave->loop->end = ((vadpcmOutputLength * 7) / 4);
			alWave->adpcmWave->loop->count = 0;

			if (hasLoopData)
			{
				alBank->eadPercussion[percussion].keyBase = *reinterpret_cast<unsigned long*> (&CN64AIFCAudio::keyTable[keyBase]);
			}
		}
		else
		{
			alWave->flags = 0;

			if (hasLoopData)
			{
				alWave->adpcmWave->loop = new ALADPCMloop();
				alWave->adpcmWave->loop->count = loopCount;
				alWave->adpcmWave->loop->start = loopStart;
				alWave->adpcmWave->loop->end = loopEnd;
				alWave->adpcmWave->loop->unknown1 = 0;
				for (int x = 0; x < 0x10; x++)
					alWave->adpcmWave->loop->state[x] = alWave->adpcmWave->book->predictors[x];
			}
		}

		delete [] pcmSamples;
		delete [] vadpcmData;
	}

	delete [] wavPCMData;

	UpdateAudioOffsets(alBank);

	return true;
}

void CN64AIFCAudio::WriteAudioToFile(ALBank*& alBank, CString outFileNameCtl, CString outFileNameTbl)
{
	unsigned char* ctl;
	unsigned char *tbl;
	int ctlSize, tblSize;
	if (alBank->soundBankFormat == STANDARDFORMAT)
	{
		WriteAudio(alBank, ctl, ctlSize, tbl, tblSize);
	}
	else if (alBank->soundBankFormat == N64PTRWAVETABLETABLEV2)
	{
		WriteAudioN64PtrWavetableV2(alBank, ctl, ctlSize, tbl, tblSize);
	}
	else if (alBank->soundBankFormat == N64PTRWAVETABLETABLEV2BLITZ)
	{
		WriteAudioN64PtrWavetableV2Blitz("", alBank, ctl, ctlSize, tbl, tblSize);
	}
	else if (alBank->soundBankFormat == N64PTRWAVETABLETABLEV1)
	{
		WriteAudioN64PtrWavetableV1(alBank, ctl, ctlSize, tbl, tblSize);
	}
	else if (alBank->soundBankFormat == SUPERMARIO64FORMAT)
	{
		//WriteAudioSuperMario(alBank, ctl, ctlSize, tbl, tblSize);
	}
	else if ((alBank->soundBankFormat == STARFOX64FORMAT) || (alBank->soundBankFormat == ZELDAFORMAT) || (alBank->soundBankFormat == FZEROFORMAT) || (alBank->soundBankFormat == TUROKFORMAT)  || (alBank->soundBankFormat == STANDARDRNCCOMPRESSED) || (alBank->soundBankFormat == STANDARDRNXCOMPRESSED) || (alBank->soundBankFormat == MARIOKART64FORMAT) || (alBank->soundBankFormat == N64PTRWAVETABLETABLEV2))
	{
		MessageBox(NULL, "Sorry, format not supported", "Error", NULL);
		return;
	}
	else if (alBank->soundBankFormat == N64PTRWAVETABLETABLEV2YAY0)
	{
		MessageBox(NULL, "Sorry, no encoding yet for YAY0 format", "Error", NULL);
		return;
	}
	else if (alBank->soundBankFormat == TAZHUFFMAN)
	{
		MessageBox(NULL, "Sorry, no encoding yet for huffman format", "Error", NULL);
		return;
	}
	else if (alBank->soundBankFormat == ARMYMENFORMAT)
	{
		MessageBox(NULL, "Sorry, no encoding yet for Army Men format", "Error", NULL);
		return;
	}
	else if (alBank->soundBankFormat == N64PTRWAVETABLETABLEV2ZLIB)
	{
		MessageBox(NULL, "Sorry, no encoding yet for ZLib N64Wave format", "Error", NULL);
		return;
	}
	else if (alBank->soundBankFormat == TITUS)
	{
		MessageBox(NULL, "Sorry, no encoding yet for Titus format", "Error", NULL);
		return;
	}
	else if (alBank->soundBankFormat == SYDNEY)
	{
		MessageBox(NULL, "Sorry, no encoding yet for Sydney format", "Error", NULL);
		return;
	}
	else if (alBank->soundBankFormat == NINDEC)
	{
		MessageBox(NULL, "Sorry, no encoding yet for NinDec format", "Error", NULL);
		return;
	}
	else if (alBank->soundBankFormat == MKMYTHOLOGIES)
	{
		MessageBox(NULL, "Sorry, no encoding yet for BOFS format", "Error", NULL);
		return;
	}
	else if (alBank->soundBankFormat == ZLIBSN64)
	{
		MessageBox(NULL, "Sorry, no encoding yet for ZLIBSN64 format", "Error", NULL);
		return;
	}
	else if (alBank->soundBankFormat == SN64)
	{
		MessageBox(NULL, "Sorry, no encoding yet for SN64 format", "Error", NULL);
		return;
	}
	else
	{
		MessageBox(NULL, "Sorry, no encoding yet for format", "Error", NULL);
		return;
	}

	FILE* outFileCtl = fopen(outFileNameCtl, "wb");
	if (outFileCtl == NULL)
	{
		MessageBox(NULL, "Cannot open ctl file", "Error", NULL);
		return;
	}

	FILE* outFileTbl = fopen(outFileNameTbl, "wb");
	if (outFileTbl == NULL)
	{
		MessageBox(NULL, "Cannot open tbl file", "Error", NULL);
		return;
	}

	fwrite(ctl, 1, ctlSize, outFileCtl);
	fwrite(tbl, 1, tblSize, outFileTbl);

	fclose(outFileCtl);
	fclose(outFileTbl);

	delete [] ctl;
	delete [] tbl;
}

void CN64AIFCAudio::WriteAudioN64PtrWavetableV1(ALBank*& alBank, unsigned char*& ctl, int& ctlSize, unsigned char*& tbl, int& tblSize)
{
	unsigned char* temporaryCtlBuffer = new unsigned char[0x1000000];
	unsigned char* temporaryTblBuffer = new unsigned char[0x1000000];
	unsigned long outputCtlCounter = 0;

	for (int x = 0; x < 0x1000000; x++)
		temporaryCtlBuffer[x] = 0x00;

	WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, 0x4E363420);
	outputCtlCounter += 4;
	WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, 0x50747254);
	outputCtlCounter += 4;
	WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, 0x61626C65);
	outputCtlCounter += 4;
	WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, 0x73202000);
	outputCtlCounter += 4;

	unsigned long outputTblCounter = 0;

	WriteLongToBuffer(temporaryTblBuffer, outputTblCounter, 0x4E363420);
	outputTblCounter += 4;
	WriteLongToBuffer(temporaryTblBuffer, outputTblCounter, 0x57617665);
	outputTblCounter += 4;
	WriteLongToBuffer(temporaryTblBuffer, outputTblCounter, 0x5461626C);
	outputTblCounter += 4;
	WriteLongToBuffer(temporaryTblBuffer, outputTblCounter, 0x65732000);
	outputTblCounter += 4;

	

	unsigned long* instrumentSoundStartLookup = new unsigned long[alBank->count];
	unsigned long* bookOffsetsWav = new unsigned long[alBank->count];
	unsigned long* adpcmRawLoopOffsetsWav = new unsigned long[alBank->count];
	unsigned long* tblOffsets = new unsigned long[alBank->count];

	WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->count);
	outputCtlCounter += 4;

	unsigned long startWriteInstrumentOffsets = outputCtlCounter;
	// placeholder
	outputCtlCounter += (alBank->count * 4);
	
	for (int x = 0; x < alBank->count; x++)
	{
		if ((outputCtlCounter % 8) != 0)
		{
			int pad = 8 - (outputCtlCounter % 8);
			for (int z = 0; z < pad; z++)
			{
				temporaryCtlBuffer[outputCtlCounter++] = 0;
			}
		}

		instrumentSoundStartLookup[x] = outputCtlCounter;

		int y = 0; // sound

		tblOffsets[x] = outputTblCounter;

		int foundSameTbl = false;

		/*for (int r = 0; r < x; r++)
		{
			int z = 0;

			if (
				(alBank->inst[x]->sounds[y]->wav.base == alBank->inst[r]->sounds[z]->wav.base)
				&& (alBank->inst[x]->sounds[y]->wav.len == alBank->inst[r]->sounds[z]->wav.len)
				)
			{
				bool mismatchValues = false;
				for (int rr = 0; rr < alBank->inst[x]->sounds[y]->wav.len; rr++)
				{
					if (alBank->inst[x]->sounds[y]->wav.wavData[rr] != alBank->inst[r]->sounds[z]->wav.wavData[rr])
					{
						mismatchValues = true;
						break;
					}
				}
				if (!mismatchValues)
				{
					foundSameTbl = true;
					tblOffsets[x] = tblOffsets[r];
					break;
				}
				else
				{
					continue;
				}
			}
		}*/

		WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, tblOffsets[x]);
		WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter + 4, alBank->inst[x]->sounds[y]->wav.len);

		if (!foundSameTbl)
		{
			for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.len; z++)
			{
				temporaryTblBuffer[outputTblCounter + z] = alBank->inst[x]->sounds[y]->wav.wavData[z];
			}
			outputTblCounter += alBank->inst[x]->sounds[y]->wav.len;

			if ((outputTblCounter % 0x10) != 0)
			{
				int pad = 0x10 - (outputTblCounter % 0x10);
				for (int z = 0; z < pad; z++)
				{
					temporaryTblBuffer[outputTblCounter++] = 0;
				}
			}
		}

		int sameLoopBank = -1;
		int sameBank = -1;

		/*if (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop != NULL)
		{
			int w = 0;
			for (int r = 0; r < x; r++)
			{
			
				if ((alBank->inst[r]->sounds[w]->wav.adpcmWave != NULL) && (alBank->inst[r]->sounds[w]->wav.adpcmWave->loop != NULL))
				{
					if ((alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start == alBank->inst[r]->sounds[w]->wav.adpcmWave->loop->start) 
						&& (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end == alBank->inst[r]->sounds[w]->wav.adpcmWave->loop->end)
						&& (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count == alBank->inst[r]->sounds[w]->wav.adpcmWave->loop->count))
					{
						bool goOn = false;
						for (int ww = 0; ww < 0x10; ww++)
						{
							if (alBank->inst[r]->sounds[w]->wav.adpcmWave->loop->state[ww] != alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[ww])
							{
								goOn = true;
								break;
							}
						}

						if (goOn)
							continue;

						adpcmRawLoopOffsetsWav[x] = adpcmRawLoopOffsetsWav[r];
						sameLoopBank = r;
						break;
					}
				}
			}
		}
		 
		

		for (int r = 0; r < x; r++)
		{
			int w = 0;

			if (alBank->inst[r]->sounds[w]->wav.adpcmWave != NULL)
			{
				if ((alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order == alBank->inst[r]->sounds[w]->wav.adpcmWave->book->order) 
					&& (alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors == alBank->inst[r]->sounds[w]->wav.adpcmWave->book->npredictors))
				{
					bool goOn = false;
					for (int ww = 0; ww < (alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8); ww++)
					{
						if (alBank->inst[r]->sounds[w]->wav.adpcmWave->book->predictors[ww] != alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[ww])
						{
							goOn = true;
							break;
						}
					}

					if (goOn)
						continue;

					sameBank = r;
					break;
				}
			}
		}*/

		
		unsigned long bookWriteSpot = outputCtlCounter + 0x10;
		unsigned long loopWriteSpot = outputCtlCounter + 0xC;

		outputCtlCounter = outputCtlCounter + 0x18;

		if (sameBank == -1)
		{
			bookOffsetsWav[x] = bookWriteSpot;
			WriteLongToBuffer(temporaryCtlBuffer, bookWriteSpot, outputCtlCounter);

			WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order);
			outputCtlCounter += 4;
			WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors);
			outputCtlCounter += 4;

			for (int z = 0; z < (alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8); z++)
			{
				temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] >> 8) & 0xFF);
				temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z]) & 0xFF);
			}

			
			// game does this not sure why
			/*int pad = 8;
			for (int z = 0; z < pad; z++)
			{
				temporaryCtlBuffer[outputCtlCounter++] = 0;
			}*/
		}
		else
		{
			bookOffsetsWav[x] = bookOffsetsWav[sameBank];
			WriteLongToBuffer(temporaryCtlBuffer, bookWriteSpot, bookOffsetsWav[sameBank]);
		}

		if (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop != NULL)
		{
			if (sameLoopBank == -1)
			{
				adpcmRawLoopOffsetsWav[x] = outputCtlCounter;
				WriteLongToBuffer(temporaryCtlBuffer, loopWriteSpot, outputCtlCounter);

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start);
				outputCtlCounter += 4;
				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end);
				outputCtlCounter += 4;
				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count);
				outputCtlCounter += 4;
				for (int z = 0; z < 0x10; z++)
				{
					temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z] >> 8) & 0xFF);
					temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z]) & 0xFF);
				}
			}
			else
			{
				adpcmRawLoopOffsetsWav[x] = adpcmRawLoopOffsetsWav[sameLoopBank];
				WriteLongToBuffer(temporaryCtlBuffer, loopWriteSpot, adpcmRawLoopOffsetsWav[sameLoopBank]);
			}
		}
		else
		{
			adpcmRawLoopOffsetsWav[x] = 0x00000000;
			// null loop
			WriteLongToBuffer(temporaryCtlBuffer, loopWriteSpot, 0x0);
		}
	}

	WriteLongToBuffer(temporaryCtlBuffer, 0x2C, outputCtlCounter);

	for (int x = 0; x < alBank->count; x++)
	{
		WriteLongToBuffer(temporaryCtlBuffer, startWriteInstrumentOffsets, instrumentSoundStartLookup[x]);
		startWriteInstrumentOffsets += 4;
	}

	delete [] instrumentSoundStartLookup;
	delete [] bookOffsetsWav;
	delete [] adpcmRawLoopOffsetsWav;
	delete [] tblOffsets;

	
	ctl = temporaryCtlBuffer;
	tbl = temporaryTblBuffer;

	ctlSize = outputCtlCounter;
	tblSize = outputTblCounter;
	
}

void CN64AIFCAudio::WriteAudioN64PtrWavetableV2(ALBank*& alBank, unsigned char*& ctl, int& ctlSize, unsigned char*& tbl, int& tblSize)
{
	unsigned char* temporaryCtlBuffer = new unsigned char[0x1000000];
	unsigned char* temporaryTblBuffer = new unsigned char[0x1000000];
	unsigned long outputCtlCounter = 0;

	for (int x = 0; x < 0x1000000; x++)
		temporaryCtlBuffer[x] = 0x00;

	WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, 0x4E363420);
	outputCtlCounter += 4;
	WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, 0x50747254);
	outputCtlCounter += 4;
	WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, 0x61626C65);
	outputCtlCounter += 4;
	WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, 0x73563200);
	outputCtlCounter += 4;

	// don't name bank
	outputCtlCounter += 0x10;
	// placeholders for offsets
	outputCtlCounter += 0x10;

	unsigned long outputTblCounter = 0;

	WriteLongToBuffer(temporaryTblBuffer, outputTblCounter, 0x4E363420);
	outputTblCounter += 4;
	WriteLongToBuffer(temporaryTblBuffer, outputTblCounter, 0x57617665);
	outputTblCounter += 4;
	WriteLongToBuffer(temporaryTblBuffer, outputTblCounter, 0x5461626C);
	outputTblCounter += 4;
	WriteLongToBuffer(temporaryTblBuffer, outputTblCounter, 0x65732000);
	outputTblCounter += 4;

	

	unsigned long* instrumentSoundStartLookup = new unsigned long[alBank->count];
	unsigned long* bookOffsetsWav = new unsigned long[alBank->count];
	unsigned long* adpcmRawLoopOffsetsWav = new unsigned long[alBank->count];
	unsigned long* tblOffsets = new unsigned long[alBank->count];

	WriteLongToBuffer(temporaryCtlBuffer, 0x20, alBank->count);
	for (int x = 0; x < alBank->count; x++)
	{
		if ((outputCtlCounter % 8) != 0)
		{
			int pad = 8 - (outputCtlCounter % 8);
			for (int z = 0; z < pad; z++)
			{
				temporaryCtlBuffer[outputCtlCounter++] = 0;
			}
		}

		instrumentSoundStartLookup[x] = outputCtlCounter;

		int y = 0; // sound

		tblOffsets[x] = outputTblCounter;

		int foundSameTbl = false;

		for (int r = 0; r < x; r++)
		{
			int z = 0;

			if (
				(alBank->inst[x]->sounds[y]->wav.base == alBank->inst[r]->sounds[z]->wav.base)
				&& (alBank->inst[x]->sounds[y]->wav.len == alBank->inst[r]->sounds[z]->wav.len)
				)
			{
				bool mismatchValues = false;
				for (int rr = 0; rr < alBank->inst[x]->sounds[y]->wav.len; rr++)
				{
					if (alBank->inst[x]->sounds[y]->wav.wavData[rr] != alBank->inst[r]->sounds[z]->wav.wavData[rr])
					{
						mismatchValues = true;
						break;
					}
				}
				if (!mismatchValues)
				{
					foundSameTbl = true;
					tblOffsets[x] = tblOffsets[r];
					break;
				}
				else
				{
					continue;
				}
			}
		}

		WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, tblOffsets[x]);
		WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter + 4, alBank->inst[x]->sounds[y]->wav.len);

		if (!foundSameTbl)
		{
			for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.len; z++)
			{
				temporaryTblBuffer[outputTblCounter + z] = alBank->inst[x]->sounds[y]->wav.wavData[z];
			}
			outputTblCounter += alBank->inst[x]->sounds[y]->wav.len;

			if ((outputTblCounter % 0x10) != 0)
			{
				int pad = 0x10 - (outputTblCounter % 0x10);
				for (int z = 0; z < pad; z++)
				{
					temporaryTblBuffer[outputTblCounter++] = 0;
				}
			}
		}

		int sameLoopBank = -1;


		if (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop != NULL)
		{
			int w = 0;
			for (int r = 0; r < x; r++)
			{
			
				if ((alBank->inst[r]->sounds[w]->wav.adpcmWave != NULL) && (alBank->inst[r]->sounds[w]->wav.adpcmWave->loop != NULL))
				{
					if ((alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start == alBank->inst[r]->sounds[w]->wav.adpcmWave->loop->start) 
						&& (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end == alBank->inst[r]->sounds[w]->wav.adpcmWave->loop->end)
						&& (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count == alBank->inst[r]->sounds[w]->wav.adpcmWave->loop->count))
					{
						bool goOn = false;
						for (int ww = 0; ww < 0x10; ww++)
						{
							if (alBank->inst[r]->sounds[w]->wav.adpcmWave->loop->state[ww] != alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[ww])
							{
								goOn = true;
								break;
							}
						}

						if (goOn)
							continue;

						adpcmRawLoopOffsetsWav[x] = adpcmRawLoopOffsetsWav[r];
						sameLoopBank = r;
						break;
					}
				}
			}
		}
		 
		int sameBank = -1;

		for (int r = 0; r < x; r++)
		{
			int w = 0;

			if (alBank->inst[r]->sounds[w]->wav.adpcmWave != NULL)
			{
				if ((alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order == alBank->inst[r]->sounds[w]->wav.adpcmWave->book->order) 
					&& (alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors == alBank->inst[r]->sounds[w]->wav.adpcmWave->book->npredictors))
				{
					bool goOn = false;
					for (int ww = 0; ww < (alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8); ww++)
					{
						if (alBank->inst[r]->sounds[w]->wav.adpcmWave->book->predictors[ww] != alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[ww])
						{
							goOn = true;
							break;
						}
					}

					if (goOn)
						continue;

					sameBank = r;
					break;
				}
			}
		}

		
		unsigned long bookWriteSpot = outputCtlCounter + 0x10;
		unsigned long loopWriteSpot = outputCtlCounter + 0xC;

		outputCtlCounter = outputCtlCounter + 0x18;

		if (sameBank == -1)
		{
			bookOffsetsWav[x] = bookWriteSpot;
			WriteLongToBuffer(temporaryCtlBuffer, bookWriteSpot, outputCtlCounter);

			WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order);
			outputCtlCounter += 4;
			WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors);
			outputCtlCounter += 4;

			for (int z = 0; z < (alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8); z++)
			{
				temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] >> 8) & 0xFF);
				temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z]) & 0xFF);
			}

			
			// game does this not sure why
			/*int pad = 8;
			for (int z = 0; z < pad; z++)
			{
				temporaryCtlBuffer[outputCtlCounter++] = 0;
			}*/
		}
		else
		{
			bookOffsetsWav[x] = bookOffsetsWav[sameBank];
			WriteLongToBuffer(temporaryCtlBuffer, bookWriteSpot, bookOffsetsWav[sameBank]);
		}

		if (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop != NULL)
		{
			if (sameLoopBank == -1)
			{
				adpcmRawLoopOffsetsWav[x] = outputCtlCounter;
				WriteLongToBuffer(temporaryCtlBuffer, loopWriteSpot, outputCtlCounter);

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start);
				outputCtlCounter += 4;
				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end);
				outputCtlCounter += 4;
				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count);
				outputCtlCounter += 4;
				for (int z = 0; z < 0x10; z++)
				{
					temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z] >> 8) & 0xFF);
					temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z]) & 0xFF);
				}
			}
			else
			{
				adpcmRawLoopOffsetsWav[x] = adpcmRawLoopOffsetsWav[sameLoopBank];
				WriteLongToBuffer(temporaryCtlBuffer, loopWriteSpot, adpcmRawLoopOffsetsWav[sameLoopBank]);
			}
		}
		else
		{
			adpcmRawLoopOffsetsWav[x] = 0x00000000;
			// null loop
			WriteLongToBuffer(temporaryCtlBuffer, loopWriteSpot, 0x0);
		}
	}

	WriteLongToBuffer(temporaryCtlBuffer, 0x2C, outputCtlCounter);

	for (int x = 0; x < alBank->count; x++)
	{
		WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, instrumentSoundStartLookup[x]);
		outputCtlCounter += 4;
	}
	WriteLongToBuffer(temporaryCtlBuffer, 0x24, outputCtlCounter);

	for (int x = 0; x < alBank->count; x++)
	{
		temporaryCtlBuffer[outputCtlCounter] = alBank->inst[x]->volume;
		outputCtlCounter++;
	}

	if ((outputCtlCounter % 4) != 0)
	{
		int pad = 4 - (outputCtlCounter % 4);
		for (int z = 0; z < pad; z++)
		{
			temporaryCtlBuffer[outputCtlCounter++] = 0;
		}
	}

	WriteLongToBuffer(temporaryCtlBuffer, 0x28, outputCtlCounter);

	delete [] instrumentSoundStartLookup;
	delete [] bookOffsetsWav;
	delete [] adpcmRawLoopOffsetsWav;
	delete [] tblOffsets;

	
	ctl = temporaryCtlBuffer;
	tbl = temporaryTblBuffer;

	ctlSize = outputCtlCounter;
	tblSize = outputTblCounter;
}

void CN64AIFCAudio::WriteAudioN64PtrWavetableV2Blitz(CString mainFolder, ALBank*& alBank, unsigned char*& ctl, int& ctlSize, unsigned char*& tbl, int& tblSize)
{
	unsigned char* ctlTemp = NULL;
	int ctlSizeTemp = 0;

	WriteAudioN64PtrWavetableV2(alBank, ctlTemp, ctlSizeTemp, tbl, tblSize);

	::SetCurrentDirectory(mainFolder);

	FILE* outFileInput = fopen(mainFolder + "tempASA3da.bin", "wb");
	if (outFileInput != NULL)
	{
		fwrite(ctlTemp, 1, ctlSizeTemp, outFileInput);
		fclose(outFileInput);

		CString tempStr;
		tempStr.Format("precomp1x.exe \"%s\" \"%s\"", mainFolder + "tempASA3da.bin", mainFolder + "tempASA3daout.bin");
		if (hiddenExec(_T(tempStr.GetBuffer()), mainFolder))
		{
			ctlSize = GetSizeFile(mainFolder + "tempASA3daout.bin");
			if (ctlSize > 0)
			{
				FILE* outFileOutput = fopen(mainFolder + "tempASA3daout.bin", "rb");
				if (outFileOutput != NULL)
				{
					ctl = new unsigned char[ctlSize];
					fread(ctl, 1, ctlSize, outFileOutput);
					fclose(outFileOutput);
				}
				else
				{
					MessageBox(NULL, "Error writing output temp file to disk", "Error", NULL);
				}
			}
			else
			{
				MessageBox(NULL, "Error empty output temp file", "Error", NULL);
			}
			::DeleteFile(mainFolder + "tempASA3da.bin");
			::DeleteFile(mainFolder + "tempASA3daout.bin");
		}
	}
	else
	{
		MessageBox(NULL, "Error writing input temp file to disk", "Error", NULL);
	}

	delete [] ctlTemp;
}

bool CN64AIFCAudio::CompareLoops(ALWave* wavIn, ALWave* wavOut)
{
	if (wavOut->adpcmWave == NULL)
		return false;

	if (wavOut->adpcmWave->loop == NULL)
		return false;

	if ((wavIn->adpcmWave->loop->start == wavOut->adpcmWave->loop->start) 
		&& (wavIn->adpcmWave->loop->end == wavOut->adpcmWave->loop->end)
		&& (wavIn->adpcmWave->loop->count == wavOut->adpcmWave->loop->count))
	{
		if (wavIn->adpcmWave->loop->start != 0)
		{
			for (int ww = 0; ww < 0x10; ww++)
			{
				if (wavIn->adpcmWave->loop->state[ww] != wavOut->adpcmWave->loop->state[ww])
				{
					return -1;
				}
			}
		}

		return true;
	}
	return false;
}

bool CN64AIFCAudio::CompareBooks(ALWave* wavIn, ALWave* wavOut)
{
	if (wavOut->adpcmWave == NULL)
		return false;

	if (wavOut->adpcmWave->book == NULL)
		return false;

	if ((wavIn->adpcmWave->book->order == wavOut->adpcmWave->book->order) 
		&& (wavIn->adpcmWave->book->npredictors == wavOut->adpcmWave->book->npredictors))
	{
		for (int ww = 0; ww < (wavIn->adpcmWave->book->order * wavIn->adpcmWave->book->npredictors * 8); ww++)
		{
			if (wavIn->adpcmWave->book->predictors[ww] != wavOut->adpcmWave->book->predictors[ww])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool CN64AIFCAudio::CompareWavs(ALWave* wavIn, ALWave* wavOut)
{
	if (wavOut->adpcmWave == NULL)
		return false;

	if (
		(wavIn->base == wavOut->base)
		&& (wavIn->len == wavOut->len)
		&& (wavIn->unknown1 == wavOut->unknown1)
		&& (wavIn->unknown2 == wavOut->unknown2)
		&& (wavIn->unknown3 == wavOut->unknown3)
		&& (wavIn->unknown4 == wavOut->unknown4)
		)
	{
		if (((wavIn->adpcmWave->loop == NULL) && (wavOut->adpcmWave->loop != NULL))
			|| ((wavIn->adpcmWave->loop != NULL) && (wavOut->adpcmWave->loop == NULL)))
		{
			return false;
		}

		if ((wavIn->adpcmWave->loop == NULL) && (wavOut->adpcmWave->loop == NULL))
		{
			
		}
		else
		{
			if (
				(wavIn->adpcmWave->loop->start == wavOut->adpcmWave->loop->start)
				&& (wavIn->adpcmWave->loop->end == wavOut->adpcmWave->loop->end)
				&& (wavIn->adpcmWave->loop->count == wavOut->adpcmWave->loop->count))
			{
				if (wavIn->adpcmWave->loop->start != 0)
				{
					for (int z = 0; z < 0x10; z++)
					{
						if (wavIn->adpcmWave->loop->state[z] != wavOut->adpcmWave->loop->state[z])
						{
							return false;
						}
					}
				}
			}
			else
			{
				return false;
			}
		}

		if ((wavIn->adpcmWave->book->npredictors == wavOut->adpcmWave->book->npredictors)
			&& (wavIn->adpcmWave->book->order == wavOut->adpcmWave->book->order))
		{
			for (int z = 0; z < (wavIn->adpcmWave->book->npredictors * wavIn->adpcmWave->book->order * 8); z++)
			{
				if (wavIn->adpcmWave->book->predictors[z] != wavOut->adpcmWave->book->predictors[z])
				{
					return false;
				}
			}

			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool CN64AIFCAudio::CompareTbls(ALWave* wavIn, ALWave* wavOut)
{
	if (
		(wavIn->len == wavOut->len)
		)
	{
		for (int rr = 0; rr < wavIn->len; rr++)
		{
			if (wavIn->wavData[rr] != wavOut->wavData[rr])
			{
				return false;
			}
		}
		
		return true;
	}
	return false;
}

void CN64AIFCAudio::WriteAudioSuperMario(std::vector<ctlTblResult>& results, unsigned char*& ctl, int& ctlSize, unsigned char*& tbl, int& tblSize)
{
	unsigned char* temporaryCtlBuffer = new unsigned char[0x1000000];
	unsigned char* temporaryTblBuffer = new unsigned char[0x1000000];
	for (int x = 0; x < 0x1000000; x++)
	{
		temporaryCtlBuffer[x] = 0;
		temporaryTblBuffer[x] = 0;
	}
	unsigned long outputCtlCounter = 0;
	
	//bank #
	int bankCount = 1;
	WriteShortToBuffer(temporaryCtlBuffer, outputCtlCounter, 0x0001);
	outputCtlCounter += 2;

	WriteShortToBuffer(temporaryCtlBuffer, outputCtlCounter, results.size());
	outputCtlCounter += 2;

	for (int x = 0; x < results.size(); x++)
	{
		// offset to bank later in file
		outputCtlCounter += 8;
	}

	if ((outputCtlCounter % 0x10) != 0)
		outputCtlCounter += ((0x10 - (outputCtlCounter % 0x10)));

	unsigned long tblSizes = 0;
	unsigned char* tblData = new unsigned char[0x1000000];

	for (int y = 0; y < 0x1000000; y++)
		tblData[y] = 0;

	std::vector<unsigned long> overallTblOffsets;
	std::vector<ALWave*> overallTblDataWaves;

	for (int soundBankNumber = 0; soundBankNumber < results.size(); soundBankNumber++)
	{
		ALBank* alBank = results[soundBankNumber].bank;

		unsigned long instrumentALLookup = 0;
		unsigned long* instrumentSoundStartLookup = new unsigned long[alBank->count+alBank->countEADPercussion];
		unsigned long* offsetsEnv = new unsigned long[alBank->count+alBank->countEADPercussion];
		unsigned long* offsetsWav = new unsigned long[alBank->count+alBank->countEADPercussion];
		unsigned long* bookOffsetsWav = new unsigned long[alBank->count+alBank->countEADPercussion];
		unsigned long* adpcmRawLoopOffsetsWav = new unsigned long[alBank->count+alBank->countEADPercussion];

		unsigned long* tblOffsets = new unsigned long[alBank->count+alBank->countEADPercussion];

		unsigned long* offsetsWavSecondary = new unsigned long[alBank->count];
		unsigned long* bookOffsetsWavSecondary = new unsigned long[alBank->count];
		unsigned long* adpcmRawLoopOffsetsWavSecondary = new unsigned long[alBank->count];

		unsigned long* tblOffsetsSecondary = new unsigned long[alBank->count];

		unsigned long* offsetsWavPrevious = new unsigned long[alBank->count];
		unsigned long* bookOffsetsWavPrevious = new unsigned long[alBank->count];
		unsigned long* adpcmRawLoopOffsetsWavPrevious = new unsigned long[alBank->count];

		unsigned long* tblOffsetsPrevious = new unsigned long[alBank->count];

		instrumentALLookup = outputCtlCounter;

		// ctl bank offset
		WriteLongToBuffer(temporaryCtlBuffer, 0x4 + (0x8 * soundBankNumber), instrumentALLookup);

		WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->count);
		outputCtlCounter += 4;
		WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->countEADPercussion);
		outputCtlCounter += 4;
		WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->unknown2);
		outputCtlCounter += 4;
		WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->unknown3);
		outputCtlCounter += 4;

		// Write percussion bank offsets here after
		outputCtlCounter += 4;

		unsigned long soundOffsetSpot = outputCtlCounter;

		outputCtlCounter += (alBank->count * 4);

		// is this 8 or 0x10?
		if ((outputCtlCounter % 0x10) != 0)
		{
			int pad = 0x10 - (outputCtlCounter % 0x10);
			for (int z = 0; z < pad; z++)
			{
				temporaryCtlBuffer[outputCtlCounter++] = 0;
			}
		}

		unsigned long soundDataOffset = instrumentALLookup + 0x10;

		for (int y = 0; y < alBank->count; y++)
		{
			if ((alBank->inst[y] != NULL) && (alBank->inst[y]->sounds != NULL) && (alBank->inst[y]->soundCount > 0))
			{
				offsetsWavPrevious[y] = (outputCtlCounter - soundDataOffset);

				if (alBank->inst[y]->sounds[0]->hasWavePrevious)
				{
					int entireMatch = -1;
					if (entireMatch == -1)
					{
						for (int w = 0; w < y; w++)
						{
							if (entireMatch != -1)
								break;

							if (alBank->inst[w]->sounds[0] != NULL)
							{
								if (!(alBank->inst[w]->sounds[0]->hasWavePrevious))
									continue;

								if (CompareWavs(&alBank->inst[y]->sounds[0]->wavPrevious, &alBank->inst[w]->sounds[0]->wavPrevious))
								{
									entireMatch = w;
									offsetsWavPrevious[y] = offsetsWavPrevious[entireMatch];
									bookOffsetsWavPrevious[y] = bookOffsetsWavPrevious[entireMatch];
									tblOffsetsPrevious[y] = tblOffsetsPrevious[entireMatch];
									break;
								}
								else
								{
									continue;
								}
							}
						}
					}


					if (entireMatch == -1)
					{
						for (int w = 0; w < y; w++)
						{
							if (entireMatch != -1)
								break;

							if (alBank->inst[w]->sounds[0] != NULL)
							{

								if (CompareWavs(&alBank->inst[y]->sounds[0]->wavPrevious, &alBank->inst[w]->sounds[0]->wav))
								{
									entireMatch = w;
									offsetsWavPrevious[y] = offsetsWav[entireMatch];
									bookOffsetsWavPrevious[y] = bookOffsetsWav[entireMatch];
									tblOffsetsPrevious[y] = tblOffsets[entireMatch];
									break;
								}
								else
								{
									continue;
								}
							}
						}
					}

					if (entireMatch == -1)
					{
						for (int w = 0; w < y; w++)
						{
							if (entireMatch != -1)
								break;

							if (alBank->inst[w]->sounds[0] != NULL)
							{
								if (!(alBank->inst[w]->sounds[0]->hasWaveSecondary))
									continue;

								if (CompareWavs(&alBank->inst[y]->sounds[0]->wavPrevious, &alBank->inst[w]->sounds[0]->wavSecondary))
								{
									entireMatch = w;
									offsetsWavPrevious[y] = offsetsWavSecondary[entireMatch];
									bookOffsetsWavPrevious[y] = bookOffsetsWavSecondary[entireMatch];
									tblOffsetsPrevious[y] = tblOffsetsSecondary[entireMatch];
									break;										
								}
								else
								{
									continue;
								}
							}
						}
					}

					if (entireMatch == -1)
					{
						int sameBook = -1;

						unsigned long loopOutputPosition = outputCtlCounter + 0x20;
						if (alBank->inst[y]->sounds[0]->wavPrevious.adpcmWave->book != NULL)
						{						
							bookOffsetsWavPrevious[y] = loopOutputPosition;

							/*if (sameBook == -1)
							{
								for (int w = 0; w < y; w++)
								{
									if (alBank->inst[w]->sounds[0] != NULL)
									{
										if (alBank->inst[w]->sounds[0]->hasWavePrevious)
										{
											if (CompareBooks(&alBank->inst[y]->sounds[0]->wavPrevious, &alBank->inst[w]->sounds[0]->wavPrevious))
											{
												sameBook = w;
												bookOffsetsWavPrevious[y] = bookOffsetsWavPrevious[x][w];
												break;
											}
										}
									}
								}
							}

							if (sameBook == -1)
							{
								for (int w = 0; w < y; w++)
								{
									if (alBank->inst[w]->sounds[0] != NULL)
									{
										if (CompareBooks(&alBank->inst[y]->sounds[0]->wavPrevious, &alBank->inst[w]->sounds[0]->wav))
										{
											sameBook = w;
											bookOffsetsWavPrevious[y] = bookOffsetsWav[x][w];
											break;
										}
									}
								}
							}

							if (sameBook == -1)
							{
								for (int w = 0; w < y; w++)
								{
									if (alBank->inst[w]->sounds[0] != NULL)
									{
										if (alBank->inst[w]->sounds[0]->hasWaveSecondary)
										{
											if (CompareBooks(&alBank->inst[y]->sounds[0]->wavPrevious, &alBank->inst[w]->sounds[0]->wavSecondary))
											{
												sameBook = w;
												bookOffsetsWavPrevious[y] = bookOffsetsWavSecondary[x][w];
												break;
											}
										}
									}
								}
							}*/

							if (sameBook == -1)
							{
								loopOutputPosition = loopOutputPosition + 0x8 + ((alBank->inst[y]->sounds[0]->wav.adpcmWave->book->npredictors * alBank->inst[y]->sounds[0]->wav.adpcmWave->book->order) * 0x10);
								if ((loopOutputPosition % 0x10) != 0)
									loopOutputPosition = (loopOutputPosition + (0x10 - (loopOutputPosition % 0x10)));
							}

						}
						else
						{
							// Used?
							MessageBox(NULL, "Error book", "Error", NULL);
						}

						int sameLoop = -1;

						if (alBank->inst[y]->sounds[0]->wav.adpcmWave->loop != NULL)
						{
							
							adpcmRawLoopOffsetsWavPrevious[y] = loopOutputPosition;

							if (alBank->inst[y]->sounds[0]->wav.adpcmWave->loop != NULL)
							{
								/*if (sameLoop == -1)
								{
									for (int w = 0; w < y; w++)
									{
										if (alBank->inst[w]->sounds[0] != NULL)
										{
											if (alBank->inst[w]->sounds[0]->hasWavePrevious)
											{
												if (CompareLoops(&alBank->inst[y]->sounds[0]->wavPrevious, &alBank->inst[w]->sounds[0]->wavPrevious))
												{
													adpcmRawLoopOffsetsWavPrevious[y] = adpcmRawLoopOffsetsWavPrevious[x][w];
													sameLoop = w;
													break;
												}
											}
										}
									}
								}

								if (sameLoop == -1)
								{
									for (int w = 0; w < y; w++)
									{
										if (alBank->inst[w]->sounds[0] != NULL)
										{
											if (CompareLoops(&alBank->inst[y]->sounds[0]->wavPrevious, &alBank->inst[w]->sounds[0]->wav))
											{
												adpcmRawLoopOffsetsWavPrevious[y] = adpcmRawLoopOffsetsWav[x][w];
												sameLoop = w;
												break;
											}
										}
									}
								}

								if (sameLoop == -1)
								{
									for (int w = 0; w < y; w++)
									{
										if (alBank->inst[w]->sounds[0] != NULL)
										{
											if (alBank->inst[w]->sounds[0]->hasWaveSecondary)
											{
												if (CompareLoops(&alBank->inst[y]->sounds[0]->wavPrevious, &alBank->inst[w]->sounds[0]->wavSecondary))
												{
													adpcmRawLoopOffsetsWavPrevious[y] = adpcmRawLoopOffsetsWavSecondary[x][w];
													sameLoop = w;
													break;
												}
											}
										}
									}
								}*/
							}
							
						}
						else
						{
							// Used?
							MessageBox(NULL, "Error loop", "Error", NULL);
						}

						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavPrevious.unknown1);
						outputCtlCounter += 4;

						tblOffsetsPrevious[y] = tblSizes;

						bool foundSameTbl = false;

						if (!foundSameTbl)
						{
							for (int z = 0; z < overallTblOffsets.size(); z++)
							{
								if (CompareTbls(&alBank->inst[y]->sounds[0]->wavPrevious, overallTblDataWaves[z]))
								{
									foundSameTbl = true;
									tblOffsetsPrevious[y] = overallTblOffsets[z];
									break;
								}
							}
						}

						if (!foundSameTbl)
						{
							int loopEnd = y;
							
							for (int z = 0; z < loopEnd; z++)
							{
								if (alBank->inst[z]->sounds[0] != NULL)
								{
									if (alBank->inst[z]->sounds[0]->hasWavePrevious)
									{
										if (CompareTbls(&alBank->inst[y]->sounds[0]->wavPrevious, &alBank->inst[z]->sounds[0]->wavPrevious))
										{
											foundSameTbl = true;
											tblOffsetsPrevious[y] = tblOffsetsPrevious[z];
											break;
										}
									}
								}
							}
						}

						if (!foundSameTbl)
						{
							int loopEnd = y;	
							for (int z = 0; z < loopEnd; z++)
							{
								if (alBank->inst[z]->sounds[0] != NULL)
								{
									if (CompareTbls(&alBank->inst[y]->sounds[0]->wavPrevious, &alBank->inst[z]->sounds[0]->wav))
									{
										foundSameTbl = true;
										tblOffsetsPrevious[y] = tblOffsets[z];
										break;
									}
								}
							}
						}

						if (!foundSameTbl)
						{
							int loopEnd = y;
							for (int z = 0; z < loopEnd; z++)
							{
								if (alBank->inst[z]->sounds[0] != NULL)
								{
									if (alBank->inst[z]->sounds[0]->hasWaveSecondary)
									{
										if (CompareTbls(&alBank->inst[y]->sounds[0]->wavPrevious, &alBank->inst[z]->sounds[0]->wavSecondary))
										{
											foundSameTbl = true;
											tblOffsetsPrevious[y] = tblOffsetsSecondary[z];
											break;
										}
									}
								}
							}
						}

						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, tblOffsetsPrevious[y]);
						outputCtlCounter += 4;


						if (!foundSameTbl)
						{
							overallTblOffsets.push_back(tblOffsetsPrevious[y]);
							overallTblDataWaves.push_back(&alBank->inst[y]->sounds[0]->wavPrevious);

							unsigned long curEntrySize = alBank->inst[y]->sounds[0]->wavPrevious.len;
							if ((alBank->inst[y]->sounds[0]->wavPrevious.len % 0x10) != 0)
								curEntrySize += (0x10 - (alBank->inst[y]->sounds[0]->wavPrevious.len % 0x10));

							for (int z = 0; z < alBank->inst[y]->sounds[0]->wavPrevious.len; z++)
							{
								tblData[tblSizes + z] = alBank->inst[y]->sounds[0]->wavPrevious.wavData[z];
							}

							tblSizes += curEntrySize;
							
							if ((tblSizes % 0x10) != 0)
							{
								tblSizes += (0x10 - (tblSizes % 0x10));
							}
						}

						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, (adpcmRawLoopOffsetsWavPrevious[y] - soundDataOffset));
						outputCtlCounter += 4;

						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, (bookOffsetsWavPrevious[y] - soundDataOffset));
						outputCtlCounter += 4;

						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavPrevious.len);
						outputCtlCounter += 4;

						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavPrevious.unknown2);
						outputCtlCounter += 4;

						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavPrevious.unknown3);
						outputCtlCounter += 4;

						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavPrevious.unknown4);
						outputCtlCounter += 4;

						if (sameBook == -1)
						{
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavPrevious.adpcmWave->book->order);
							outputCtlCounter += 4;
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavPrevious.adpcmWave->book->npredictors);
							outputCtlCounter += 4;


							for (int z = 0; z < (alBank->inst[y]->sounds[0]->wavPrevious.adpcmWave->book->order * alBank->inst[y]->sounds[0]->wavPrevious.adpcmWave->book->npredictors * 8); z++)
							{
								temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[y]->sounds[0]->wavPrevious.adpcmWave->book->predictors[z] >> 8) & 0xFF);
								temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[y]->sounds[0]->wavPrevious.adpcmWave->book->predictors[z]) & 0xFF);
							}

							if ((outputCtlCounter % 0x10) != 0)
								outputCtlCounter = outputCtlCounter + (0x10 - (outputCtlCounter % 0x10));
						}

						if (sameLoop == -1)
						{

							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavPrevious.adpcmWave->loop->start);
							outputCtlCounter += 4;
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavPrevious.adpcmWave->loop->end);
							outputCtlCounter += 4;
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavPrevious.adpcmWave->loop->count);
							outputCtlCounter += 4;
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavPrevious.adpcmWave->loop->unknown1);
							outputCtlCounter += 4;

							if (alBank->inst[y]->sounds[0]->wavPrevious.adpcmWave->loop->start != 0)
							{
								for (int z = 0; z < 0x10; z++)
								{
									temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[y]->sounds[0]->wavPrevious.adpcmWave->loop->state[z] >> 8) & 0xFF);
									temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[y]->sounds[0]->wavPrevious.adpcmWave->loop->state[z]) & 0xFF);
								}
							}

							if ((outputCtlCounter % 0x10) != 0)
								outputCtlCounter = outputCtlCounter + (0x10 - (outputCtlCounter % 0x10));
						}
					}
				}





				offsetsWav[y] = (outputCtlCounter - soundDataOffset);

				int entireMatch = -1;
				if (entireMatch == -1)
				{
					for (int w = 0; w < (y + 1); w++)
					{
						if (entireMatch != -1)
							break;

						if (alBank->inst[w]->sounds[0] != NULL)
						{
							if (!(alBank->inst[w]->sounds[0]->hasWavePrevious))
								continue;

							if (CompareWavs(&alBank->inst[y]->sounds[0]->wav, &alBank->inst[w]->sounds[0]->wavPrevious))
							{
								entireMatch = w;
								offsetsWav[y] = offsetsWavPrevious[entireMatch];
								bookOffsetsWav[y] = bookOffsetsWavPrevious[entireMatch];
								tblOffsets[y] = tblOffsetsPrevious[entireMatch];
								break;
							}
							else
							{
								continue;
							}
						}
					}
				}


				if (entireMatch == -1)
				{
					for (int w = 0; w < y; w++)
					{
						if (entireMatch != -1)
							break;

						if (alBank->inst[w]->sounds[0] != NULL)
						{
							if (CompareWavs(&alBank->inst[y]->sounds[0]->wav, &alBank->inst[w]->sounds[0]->wav))
							{
								entireMatch = w;
								offsetsWav[y] = offsetsWav[entireMatch];
								bookOffsetsWav[y] = bookOffsetsWav[entireMatch];
								tblOffsets[y] = tblOffsets[entireMatch];
								break;
							}
							else
							{
								continue;
							}
						}
					}
				}

				if (entireMatch == -1)
				{
					for (int w = 0; w < y; w++)
					{
						if (entireMatch != -1)
							break;

						if (alBank->inst[w]->sounds[0] != NULL)
						{
							if (!(alBank->inst[w]->sounds[0]->hasWaveSecondary))
								continue;

							if (CompareWavs(&alBank->inst[y]->sounds[0]->wav, &alBank->inst[w]->sounds[0]->wavSecondary))
							{
								entireMatch = w;
								offsetsWav[y] = offsetsWavSecondary[entireMatch];
								bookOffsetsWav[y] = bookOffsetsWavSecondary[entireMatch];
								tblOffsets[y] = tblOffsetsSecondary[entireMatch];
								break;
							}
						}
					}
				}

				if (entireMatch == -1)
				{
					int sameBook = -1;

					unsigned long loopOutputPosition = outputCtlCounter + 0x20;
					if (alBank->inst[y]->sounds[0]->wav.adpcmWave->book != NULL)
					{						
						bookOffsetsWav[y] = loopOutputPosition;

						/*if (sameBook == -1)
						{
							for (int w = 0; w < (y + 1); w++)
							{
								if (alBank->inst[w]->sounds[0] != NULL)
								{
									if (alBank->inst[w]->sounds[0]->hasWavePrevious)
									{
										if (CompareBooks(&alBank->inst[y]->sounds[0]->wav, &alBank->inst[w]->sounds[0]->wavPrevious))
										{
											sameBook = w;
											bookOffsetsWav[y] = bookOffsetsWavPrevious[x][w];
											break;
										}
									}
								}
							}
						}

						if (sameBook == -1)
						{
							for (int w = 0; w < y; w++)
							{
								if (alBank->inst[w]->sounds[0] != NULL)
								{
									if (CompareBooks(&alBank->inst[y]->sounds[0]->wav, &alBank->inst[w]->sounds[0]->wav))
									{
										sameBook = w;
										bookOffsetsWav[y] = bookOffsetsWav[x][w];
										break;
									}
								}
							}
						}

						if (sameBook == -1)
						{
							for (int w = 0; w < y; w++)
							{
								if (alBank->inst[w]->sounds[0] != NULL)
								{
									if (alBank->inst[w]->sounds[0]->hasWaveSecondary)
									{
										if (CompareBooks(&alBank->inst[y]->sounds[0]->wav, &alBank->inst[w]->sounds[0]->wavSecondary))
										{
											sameBook = w;
											bookOffsetsWav[y] = bookOffsetsWavSecondary[x][w];
											break;
										}
									}
								}
							}
						}*/

						if (sameBook == -1)
						{
							loopOutputPosition = loopOutputPosition + 0x8 + ((alBank->inst[y]->sounds[0]->wav.adpcmWave->book->npredictors * alBank->inst[y]->sounds[0]->wav.adpcmWave->book->order) * 0x10);
							if ((loopOutputPosition % 0x10) != 0)
								loopOutputPosition = (loopOutputPosition + (0x10 - (loopOutputPosition % 0x10)));
						}

					}
					else
					{
						// Used?
						MessageBox(NULL, "Error book", "Error", NULL);
					}

					int sameLoop = -1;

					if (alBank->inst[y]->sounds[0]->wav.adpcmWave->loop != NULL)
					{
						
						adpcmRawLoopOffsetsWav[y] = loopOutputPosition;

						if (alBank->inst[y]->sounds[0]->wav.adpcmWave->loop != NULL)
						{
							/*if (sameLoop == -1)
							{
								for (int w = 0; w < (y + 1); w++)
								{
									if (alBank->inst[w]->sounds[0] != NULL)
									{
										if (alBank->inst[w]->sounds[0]->hasWavePrevious)
										{
											if (CompareLoops(&alBank->inst[y]->sounds[0]->wav, &alBank->inst[w]->sounds[0]->wavPrevious))
											{
												adpcmRawLoopOffsetsWav[y] = adpcmRawLoopOffsetsWavPrevious[x][w];
												sameLoop = w;
												break;
											}
										}
									}
								}
							}

							if (sameLoop == -1)
							{
								for (int w = 0; w < y; w++)
								{
									if (alBank->inst[w]->sounds[0] != NULL)
									{
										if (CompareLoops(&alBank->inst[y]->sounds[0]->wav, &alBank->inst[w]->sounds[0]->wav))
										{
											adpcmRawLoopOffsetsWav[y] = adpcmRawLoopOffsetsWav[x][w];
											sameLoop = w;
											break;
										}
									}
								}
							}

							if (sameLoop == -1)
							{
								for (int w = 0; w < y; w++)
								{
									if (alBank->inst[w]->sounds[0] != NULL)
									{
										if (alBank->inst[w]->sounds[0]->hasWaveSecondary)
										{
											if (CompareLoops(&alBank->inst[y]->sounds[0]->wav, &alBank->inst[w]->sounds[0]->wavSecondary))
											{
												adpcmRawLoopOffsetsWav[y] = adpcmRawLoopOffsetsWavSecondary[x][w];
												sameLoop = w;
												break;
											}
										}
									}
								}
							}*/
						}
						
					}
					else
					{
						// Used?
						MessageBox(NULL, "Error loop", "Error", NULL);
					}

					WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wav.unknown1);
					outputCtlCounter += 4;

					tblOffsets[y] = tblSizes;

					bool foundSameTbl = false;

					if (!foundSameTbl)
					{
						for (int z = 0; z < overallTblOffsets.size(); z++)
						{
							if (CompareTbls(&alBank->inst[y]->sounds[0]->wav, overallTblDataWaves[z]))
							{
								foundSameTbl = true;
								tblOffsets[y] = overallTblOffsets[z];
								break;
							}
						}
					}

					if (!foundSameTbl)
					{
						int loopEnd = y;
						for (int z = 0; z < loopEnd; z++)
						{
							if (alBank->inst[z]->sounds[0] != NULL)
							{
								if (alBank->inst[z]->sounds[0]->hasWavePrevious)
								{
									if (CompareTbls(&alBank->inst[y]->sounds[0]->wav, &alBank->inst[z]->sounds[0]->wavPrevious))
									{
										foundSameTbl = true;
										tblOffsets[y] = tblOffsetsPrevious[z];
										break;
									}
								}
							}
						}
					}

					if (!foundSameTbl)
					{
						int loopEnd = y;
						for (int z = 0; z < loopEnd; z++)
						{
							if (alBank->inst[z]->sounds[0] != NULL)
							{
								if (CompareTbls(&alBank->inst[y]->sounds[0]->wav, &alBank->inst[z]->sounds[0]->wav))
								{
									foundSameTbl = true;
									tblOffsets[y] = tblOffsets[z];
									break;
								}
							}
						}
					}

					if (!foundSameTbl)
					{
						int loopEnd = y;
						for (int z = 0; z < loopEnd; z++)
						{
							if (alBank->inst[z]->sounds[0] != NULL)
							{
								if (alBank->inst[z]->sounds[0]->hasWaveSecondary)
								{
									if (CompareTbls(&alBank->inst[y]->sounds[0]->wav, &alBank->inst[z]->sounds[0]->wavSecondary))
									{
										foundSameTbl = true;
										tblOffsets[y] = tblOffsetsSecondary[z];
										break;
									}
								}
							}
						}
					}

					WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, tblOffsets[y]);
					outputCtlCounter += 4;


					if (!foundSameTbl)
					{
						overallTblOffsets.push_back(tblOffsets[y]);
						overallTblDataWaves.push_back(&alBank->inst[y]->sounds[0]->wav);

						unsigned long curEntrySize = alBank->inst[y]->sounds[0]->wav.len;
						if ((alBank->inst[y]->sounds[0]->wav.len % 0x10) != 0)
							curEntrySize += (0x10 - (alBank->inst[y]->sounds[0]->wav.len % 0x10));

						for (int z = 0; z < alBank->inst[y]->sounds[0]->wav.len; z++)
						{
							tblData[tblSizes + z] = alBank->inst[y]->sounds[0]->wav.wavData[z];
						}

						tblSizes += curEntrySize;
						
						if ((tblSizes % 0x10) != 0)
						{
							tblSizes += (0x10 - (tblSizes % 0x10));
						}
					}

					WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, (adpcmRawLoopOffsetsWav[y] - soundDataOffset));
					outputCtlCounter += 4;

					WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, (bookOffsetsWav[y] - soundDataOffset));
					outputCtlCounter += 4;

					WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wav.len);
					outputCtlCounter += 4;

					WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wav.unknown2);
					outputCtlCounter += 4;

					WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wav.unknown3);
					outputCtlCounter += 4;

					WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wav.unknown4);
					outputCtlCounter += 4;

					if (sameBook == -1)
					{
						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wav.adpcmWave->book->order);
						outputCtlCounter += 4;
						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wav.adpcmWave->book->npredictors);
						outputCtlCounter += 4;
						
						for (int z = 0; z < (alBank->inst[y]->sounds[0]->wav.adpcmWave->book->order * alBank->inst[y]->sounds[0]->wav.adpcmWave->book->npredictors * 8); z++)
						{
							temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[y]->sounds[0]->wav.adpcmWave->book->predictors[z] >> 8) & 0xFF);
							temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[y]->sounds[0]->wav.adpcmWave->book->predictors[z]) & 0xFF);
						}

						if ((outputCtlCounter % 0x10) != 0)
							outputCtlCounter = outputCtlCounter + (0x10 - (outputCtlCounter % 0x10));
					}

					if (sameLoop == -1)
					{
						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wav.adpcmWave->loop->start);
						outputCtlCounter += 4;
						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wav.adpcmWave->loop->end);
						outputCtlCounter += 4;
						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wav.adpcmWave->loop->count);
						outputCtlCounter += 4;
						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wav.adpcmWave->loop->unknown1);
						outputCtlCounter += 4;

						if (alBank->inst[y]->sounds[0]->wav.adpcmWave->loop->start != 0)
						{
							for (int z = 0; z < 0x10; z++)
							{
								temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[y]->sounds[0]->wav.adpcmWave->loop->state[z] >> 8) & 0xFF);
								temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[y]->sounds[0]->wav.adpcmWave->loop->state[z]) & 0xFF);
							}
						}

						if ((outputCtlCounter % 0x10) != 0)
							outputCtlCounter = outputCtlCounter + (0x10 - (outputCtlCounter % 0x10));
					}
				}

				offsetsWavSecondary[y] = (outputCtlCounter - soundDataOffset);

				if (alBank->inst[y]->sounds[0]->hasWaveSecondary)
				{


					int entireMatch = -1;
					if (entireMatch == -1)
					{
						for (int w = 0; w < (y + 1); w++)
						{
							if (entireMatch != -1)
								break;

							if (alBank->inst[w]->sounds[0] != NULL)
							{
								if (!(alBank->inst[w]->sounds[0]->hasWavePrevious))
									continue;

								if (CompareWavs(&alBank->inst[y]->sounds[0]->wavSecondary, &alBank->inst[w]->sounds[0]->wavPrevious))
								{
									entireMatch = w;
									offsetsWavSecondary[y] = offsetsWavPrevious[entireMatch];
									bookOffsetsWavSecondary[y] = bookOffsetsWavPrevious[entireMatch];
									tblOffsetsSecondary[y] = tblOffsetsPrevious[entireMatch];
									break;
								}
								else
								{
									continue;
								}
							}
						}
					}


					if (entireMatch == -1)
					{
						for (int w = 0; w < (y + 1); w++)
						{
							if (entireMatch != -1)
								break;

							if (alBank->inst[w]->sounds[0] != NULL)
							{

								if (CompareWavs(&alBank->inst[y]->sounds[0]->wavSecondary, &alBank->inst[w]->sounds[0]->wav))
								{
									entireMatch = w;
									offsetsWavSecondary[y] = offsetsWav[entireMatch];
									bookOffsetsWavSecondary[y] = bookOffsetsWav[entireMatch];
									tblOffsetsSecondary[y] = tblOffsets[entireMatch];
									break;
								}
								else
								{
									continue;
								}
							}
						}
					}

					if (entireMatch == -1)
					{
						for (int w = 0; w < y; w++)
						{
							if (entireMatch != -1)
								break;

							if (alBank->inst[w]->sounds[0] != NULL)
							{
								if (!(alBank->inst[w]->sounds[0]->hasWaveSecondary))
									continue;

								if (CompareWavs(&alBank->inst[y]->sounds[0]->wavSecondary, &alBank->inst[w]->sounds[0]->wavSecondary))
								{
									entireMatch = w;
									offsetsWavSecondary[y] = offsetsWavSecondary[entireMatch];
									bookOffsetsWavSecondary[y] = bookOffsetsWavSecondary[entireMatch];
									tblOffsetsSecondary[y] = tblOffsetsSecondary[entireMatch];
									break;
								}
								else
								{
									continue;
								}
							}
						}
					}

					if (entireMatch == -1)
					{
						int sameBook = -1;

						unsigned long loopOutputPosition = outputCtlCounter + 0x20;
						if (alBank->inst[y]->sounds[0]->wavSecondary.adpcmWave->book != NULL)
						{						
							bookOffsetsWavSecondary[y] = loopOutputPosition;

							/*if (sameBook == -1)
							{
								for (int w = 0; w < (y + 1); w++)
								{
									if (alBank->inst[w]->sounds[0] != NULL)
									{
										if (alBank->inst[w]->sounds[0]->hasWavePrevious)
										{
											if (CompareBooks(&alBank->inst[y]->sounds[0]->wavSecondary, &alBank->inst[w]->sounds[0]->wavPrevious))
											{
												sameBook = w;
												bookOffsetsWavSecondary[y] = bookOffsetsWavPrevious[x][w];
												break;
											}
										}
									}
								}
							}

							if (sameBook == -1)
							{
								for (int w = 0; w < (y + 1); w++)
								{
									if (alBank->inst[w]->sounds[0] != NULL)
									{
										if (CompareBooks(&alBank->inst[y]->sounds[0]->wavSecondary, &alBank->inst[w]->sounds[0]->wav))
										{
											sameBook = w;
											bookOffsetsWavSecondary[y] = bookOffsetsWav[x][w];
											break;
										}
									}
								}
							}

							if (sameBook == -1)
							{
								for (int w = 0; w < y; w++)
								{
									if (alBank->inst[w]->sounds[0] != NULL)
									{
										if (alBank->inst[w]->sounds[0]->hasWaveSecondary)
										{
											if (CompareBooks(&alBank->inst[y]->sounds[0]->wavSecondary, &alBank->inst[w]->sounds[0]->wavSecondary))
											{
												sameBook = w;
												bookOffsetsWavSecondary[y] = bookOffsetsWavSecondary[x][w];
												break;
											}
										}
									}
								}
							}*/

							if (sameBook == -1)
							{
								loopOutputPosition = loopOutputPosition + 0x8 + ((alBank->inst[y]->sounds[0]->wav.adpcmWave->book->npredictors * alBank->inst[y]->sounds[0]->wav.adpcmWave->book->order) * 0x10);
								if ((loopOutputPosition % 0x10) != 0)
									loopOutputPosition = (loopOutputPosition + (0x10 - (loopOutputPosition % 0x10)));
							}

						}
						else
						{
							// Used?
							MessageBox(NULL, "Error book", "Error", NULL);
						}

						int sameLoop = -1;

						if (alBank->inst[y]->sounds[0]->wavSecondary.adpcmWave->loop != NULL)
						{
							
							adpcmRawLoopOffsetsWavSecondary[y] = loopOutputPosition;

							if (alBank->inst[y]->sounds[0]->wavSecondary.adpcmWave->loop != NULL)
							{
								/*if (sameLoop == -1)
								{
									for (int w = 0; w < (y + 1); w++)
									{
										if (alBank->inst[w]->sounds[0] != NULL)
										{
											if (alBank->inst[w]->sounds[0]->hasWavePrevious)
											{
												if (CompareLoops(&alBank->inst[y]->sounds[0]->wavSecondary, &alBank->inst[w]->sounds[0]->wavPrevious))
												{
													adpcmRawLoopOffsetsWavSecondary[y] = adpcmRawLoopOffsetsWavPrevious[x][w];
													sameLoop = w;
													break;
												}
											}
										}
									}
								}

								if (sameLoop == -1)
								{
									for (int w = 0; w < (y + 1); w++)
									{
										if (alBank->inst[w]->sounds[0] != NULL)
										{
											if (CompareLoops(&alBank->inst[y]->sounds[0]->wavSecondary, &alBank->inst[w]->sounds[0]->wav))
											{
												adpcmRawLoopOffsetsWavSecondary[y] = adpcmRawLoopOffsetsWav[x][w];
												sameLoop = w;
												break;
											}
										}
									}
								}

								if (sameLoop == -1)
								{
									for (int w = 0; w < y; w++)
									{
										if (alBank->inst[w]->sounds[0] != NULL)
										{
											if (alBank->inst[w]->sounds[0]->hasWaveSecondary)
											{
												if (CompareLoops(&alBank->inst[y]->sounds[0]->wavSecondary, &alBank->inst[w]->sounds[0]->wavSecondary))
												{
													adpcmRawLoopOffsetsWavSecondary[y] = adpcmRawLoopOffsetsWavSecondary[x][w];
													sameLoop = w;
													break;
												}
											}
										}
									}
								}*/
							}
						}
						else
						{
							// Used?
							MessageBox(NULL, "Error loop", "Error", NULL);
						}

						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavSecondary.unknown1);
						outputCtlCounter += 4;

						tblOffsetsSecondary[y] = tblSizes;

						bool foundSameTbl = false;

						if (!foundSameTbl)
						{
							for (int z = 0; z < overallTblOffsets.size(); z++)
							{
								if (CompareTbls(&alBank->inst[y]->sounds[0]->wavSecondary, overallTblDataWaves[z]))
								{
									foundSameTbl = true;
									tblOffsetsSecondary[y] = overallTblOffsets[z];
									break;
								}
							}
						}
						
						if (!foundSameTbl)
						{
							int loopEnd = (y + 1);
							for (int z = 0; z < loopEnd; z++)
							{
								if (alBank->inst[z]->sounds[0] != NULL)
								{
									if (alBank->inst[z]->sounds[0]->hasWavePrevious)
									{
										if (CompareTbls(&alBank->inst[y]->sounds[0]->wavSecondary, &alBank->inst[z]->sounds[0]->wavPrevious))
										{
											foundSameTbl = true;
											tblOffsetsSecondary[y] = tblOffsetsPrevious[z];
											break;
										}
									}
								}
							}
						}

						if (!foundSameTbl)
						{
							int loopEnd = (y + 1);
							
							for (int z = 0; z < loopEnd; z++)
							{
								if (alBank->inst[z]->sounds[0] != NULL)
								{
									if (CompareTbls(&alBank->inst[y]->sounds[0]->wavSecondary, &alBank->inst[z]->sounds[0]->wav))
									{
										foundSameTbl = true;
										tblOffsetsSecondary[y] = tblOffsets[z];
										break;
									}
								}
							}
						}

						if (!foundSameTbl)
						{
							int loopEnd = y;
							for (int z = 0; z < loopEnd; z++)
							{
								if (alBank->inst[z]->sounds[0] != NULL)
								{
									if (alBank->inst[z]->sounds[0]->hasWaveSecondary)
									{
										if (CompareTbls(&alBank->inst[y]->sounds[0]->wavSecondary, &alBank->inst[z]->sounds[0]->wavSecondary))
										{
											foundSameTbl = true;
											tblOffsetsSecondary[y] = tblOffsetsSecondary[z];
											break;
										}
									}
								}
							}
						}

						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, tblOffsetsSecondary[y]);
						outputCtlCounter += 4;


						if (!foundSameTbl)
						{
							overallTblOffsets.push_back(tblOffsetsSecondary[y]);
							overallTblDataWaves.push_back(&alBank->inst[y]->sounds[0]->wavSecondary);

							unsigned long curEntrySize = alBank->inst[y]->sounds[0]->wavSecondary.len;
							if ((alBank->inst[y]->sounds[0]->wavSecondary.len % 0x10) != 0)
								curEntrySize += (0x10 - (alBank->inst[y]->sounds[0]->wavSecondary.len % 0x10));

							for (int z = 0; z < alBank->inst[y]->sounds[0]->wavSecondary.len; z++)
							{
								tblData[tblSizes + z] = alBank->inst[y]->sounds[0]->wavSecondary.wavData[z];
							}

							tblSizes += curEntrySize;
							
							if ((tblSizes % 0x10) != 0)
							{
								tblSizes += (0x10 - (tblSizes % 0x10));
							}
						}

						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, (adpcmRawLoopOffsetsWavSecondary[y] - soundDataOffset));
						outputCtlCounter += 4;

						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, (bookOffsetsWavSecondary[y] - soundDataOffset));
						outputCtlCounter += 4;

						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavSecondary.len);
						outputCtlCounter += 4;

						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavSecondary.unknown2);
						outputCtlCounter += 4;

						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavSecondary.unknown3);
						outputCtlCounter += 4;

						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavSecondary.unknown4);
						outputCtlCounter += 4;

						
						if (sameBook == -1)
						{
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavSecondary.adpcmWave->book->order);
							outputCtlCounter += 4;
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavSecondary.adpcmWave->book->npredictors);
							outputCtlCounter += 4;

							for (int z = 0; z < (alBank->inst[y]->sounds[0]->wavSecondary.adpcmWave->book->order * alBank->inst[y]->sounds[0]->wavSecondary.adpcmWave->book->npredictors * 8); z++)
							{
								temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[y]->sounds[0]->wavSecondary.adpcmWave->book->predictors[z] >> 8) & 0xFF);
								temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[y]->sounds[0]->wavSecondary.adpcmWave->book->predictors[z]) & 0xFF);
							}

							if ((outputCtlCounter % 0x10) != 0)
								outputCtlCounter = outputCtlCounter + (0x10 - (outputCtlCounter % 0x10));
						}

						if (sameLoop == -1)
						{
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavSecondary.adpcmWave->loop->start);
							outputCtlCounter += 4;
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavSecondary.adpcmWave->loop->end);
							outputCtlCounter += 4;
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavSecondary.adpcmWave->loop->count);
							outputCtlCounter += 4;
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->wavSecondary.adpcmWave->loop->unknown1);
							outputCtlCounter += 4;

							if (alBank->inst[y]->sounds[0]->wavSecondary.adpcmWave->loop->start != 0)
							{
								for (int z = 0; z < 0x10; z++)
								{
									temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[y]->sounds[0]->wavSecondary.adpcmWave->loop->state[z] >> 8) & 0xFF);
									temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[y]->sounds[0]->wavSecondary.adpcmWave->loop->state[z]) & 0xFF);
								}
							}

							if ((outputCtlCounter % 0x10) != 0)
								outputCtlCounter = outputCtlCounter + (0x10 - (outputCtlCounter % 0x10));
						}
					}
				}
			}
		}

		int startPercussionInListing = alBank->count;

		for (int y = 0; y < alBank->countEADPercussion; y++)
		{
			offsetsWav[startPercussionInListing+y] = (outputCtlCounter - soundDataOffset);

			int entireMatch = -1;
			if (entireMatch == -1)
			{
				for (int w = 0; w < alBank->count; w++)
				{
					if (entireMatch != -1)
						break;

					if (alBank->inst[w]->sounds[0] != NULL)
					{
						
						if (!alBank->inst[w]->sounds[0]->hasWavePrevious)
							continue;

						if (CompareWavs(&alBank->eadPercussion[y].wav, &alBank->inst[w]->sounds[0]->wavPrevious))
						{
							entireMatch = w;
							offsetsWav[startPercussionInListing+y] = offsetsWavPrevious[entireMatch];
							bookOffsetsWav[startPercussionInListing+y] = bookOffsetsWavPrevious[entireMatch];
							tblOffsets[startPercussionInListing+y] = tblOffsetsPrevious[entireMatch];
							break;
						}
					}
				}
			}

			if (entireMatch == -1)
			{
				for (int w = 0; w < alBank->count; w++)
				{
					if (entireMatch != -1)
						break;

					if (alBank->inst[w]->sounds[0] != NULL)
					{
						if (CompareWavs(&alBank->eadPercussion[y].wav, &alBank->inst[w]->sounds[0]->wav))
						{
							entireMatch = w;
							offsetsWav[startPercussionInListing+y] = offsetsWav[entireMatch];
							bookOffsetsWav[startPercussionInListing+y] = bookOffsetsWav[entireMatch];
							tblOffsets[startPercussionInListing+y] = tblOffsets[entireMatch];
							break;
						}
					}
				}
			}

			if (entireMatch == -1)
			{
				for (int w = 0; w < alBank->count; w++)
				{
					if (entireMatch != -1)
						break;

					if (alBank->inst[w]->sounds[0] != NULL)
					{
						if (!alBank->inst[w]->sounds[0]->hasWaveSecondary)
							continue;

						if (CompareWavs(&alBank->eadPercussion[y].wav, &alBank->inst[w]->sounds[0]->wavSecondary))
						{
							entireMatch = w;
							offsetsWav[startPercussionInListing+y] = offsetsWavSecondary[entireMatch];
							bookOffsetsWav[startPercussionInListing+y] = bookOffsetsWavSecondary[entireMatch];
							tblOffsets[startPercussionInListing+y] = tblOffsetsSecondary[entireMatch];
							break;
						}
					}
				}
			}

			if (entireMatch == -1)
			{				
				for (int w = 0; w < y; w++)
				{
					if (entireMatch != -1)
						break;


					if (CompareWavs(&alBank->eadPercussion[y].wav, &alBank->eadPercussion[w].wav))
					{
						entireMatch = w;
						offsetsWav[startPercussionInListing+y] = offsetsWav[startPercussionInListing+w];
						bookOffsetsWav[startPercussionInListing+y] = bookOffsetsWav[startPercussionInListing+w];
						tblOffsets[startPercussionInListing+y] = tblOffsets[startPercussionInListing+w];
						break;
					}
				}
			}



			if (entireMatch == -1)
			{
				int sameBook = -1;

				unsigned long loopOutputPosition = outputCtlCounter + 0x20;
				if (alBank->eadPercussion[y].wav.adpcmWave->book != NULL)
				{						
					bookOffsetsWav[startPercussionInListing+y] = loopOutputPosition;

					/*if (sameBook == -1)
					{
						for (int w = 0; w < alBank->count; w++)
						{
							if (alBank->inst[w]->sounds[0] != NULL)
							{
								if (alBank->inst[w]->sounds[0]->hasWavePrevious)
								{
									if (CompareBooks(&alBank->eadPercussion[y].wav, &alBank->inst[w]->sounds[0]->wavPrevious))
									{
										sameBook = w;
										bookOffsetsWav[startPercussionInListing+y] = bookOffsetsWavPrevious[x][w];
										break;
									}
								}
							}
						}
					}

					if (sameBook == -1)
					{
						for (int w = 0; w < alBank->count; w++)
						{
							if (alBank->inst[w]->sounds[0] != NULL)
							{
								if (CompareBooks(&alBank->eadPercussion[y].wav, &alBank->inst[w]->sounds[0]->wav))
								{
									sameBook = w;
									bookOffsetsWav[startPercussionInListing+y] = bookOffsetsWav[x][w];
									break;
								}
							}
						}
					}

					if (sameBook == -1)
					{
						for (int w = 0; w < alBank->count; w++)
						{
							if (alBank->inst[w]->sounds[0] != NULL)
							{
								if (alBank->inst[w]->sounds[0]->hasWaveSecondary)
								{
									if (CompareBooks(&alBank->eadPercussion[y].wav, &alBank->inst[w]->sounds[0]->wavSecondary))
									{
										sameBook = w;
										bookOffsetsWav[startPercussionInListing+y] = bookOffsetsWavSecondary[x][w];
										break;
									}
								}
							}
						}
					}

					if (sameBook == -1)
					{
						for (int w = 0; w < y; w++)
						{
							if (CompareBooks(&alBank->eadPercussion[y].wav, &alBank->inst[x]->eadPercussion[w].wav))
							{
								sameBook = w;
								bookOffsetsWav[startPercussionInListing+y] = bookOffsetsWav[x][startPercussionInListing+w];
								break;
							}
						}
					}*/

					if (sameBook == -1)
					{
						loopOutputPosition = loopOutputPosition + 0x8 + ((alBank->eadPercussion[y].wav.adpcmWave->book->npredictors * alBank->eadPercussion[y].wav.adpcmWave->book->order) * 0x10);
						if ((loopOutputPosition % 0x10) != 0)
							loopOutputPosition = (loopOutputPosition + (0x10 - (loopOutputPosition % 0x10)));
					}

				}
				else
				{
					// Used?
					MessageBox(NULL, "Error book", "Error", NULL);
				}

				int sameLoop = -1;

				if (alBank->eadPercussion[y].wav.adpcmWave->loop != NULL)
				{
					
					adpcmRawLoopOffsetsWav[startPercussionInListing+y] = loopOutputPosition;

					if (alBank->eadPercussion[y].wav.adpcmWave->loop != NULL)
					{
						/*if (sameLoop == -1)
						{
							for (int w = 0; w < alBank->count; w++)
							{
								if (alBank->inst[w]->sounds[0] != NULL)
								{
									if (alBank->inst[w]->sounds[0]->hasWavePrevious)
									{
										if (CompareLoops(&alBank->eadPercussion[y].wav, &alBank->inst[w]->sounds[0]->wavPrevious))
										{
											adpcmRawLoopOffsetsWav[startPercussionInListing+y] = adpcmRawLoopOffsetsWavPrevious[x][w];
											sameLoop = w;
											break;
										}
									}
								}
							}
						}

						if (sameLoop == -1)
						{
							for (int w = 0; w < alBank->count; w++)
							{
								if (alBank->inst[w]->sounds[0] != NULL)
								{
									if (CompareLoops(&alBank->eadPercussion[y].wav, &alBank->inst[w]->sounds[0]->wav))
									{
										adpcmRawLoopOffsetsWav[startPercussionInListing+y] = adpcmRawLoopOffsetsWav[x][w];
										sameLoop = w;
										break;
									}
								}
							}
						}

						if (sameLoop == -1)
						{
							for (int w = 0; w < alBank->count; w++)
							{
								if (alBank->inst[w]->sounds[0] != NULL)
								{
									if (alBank->inst[w]->sounds[0]->hasWaveSecondary)
									{
										if (CompareLoops(&alBank->eadPercussion[y].wav, &alBank->inst[w]->sounds[0]->wavSecondary))
										{
											adpcmRawLoopOffsetsWav[startPercussionInListing+y] = adpcmRawLoopOffsetsWavSecondary[x][w];
											sameLoop = w;
											break;
										}
									}
								}
							}
						}

						if (sameLoop == -1)
						{
							for (int w = 0; w < y; w++)
							{
								if (CompareLoops(&alBank->eadPercussion[y].wav, &alBank->inst[x]->eadPercussion[w].wav))
								{
									sameBook = w;
									adpcmRawLoopOffsetsWav[startPercussionInListing+y] = adpcmRawLoopOffsetsWav[x][startPercussionInListing+w];
								}
							}
						}*/
					}
					
				}
				else
				{
					// Used?
					MessageBox(NULL, "Error loop", "Error", NULL);
				}

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->eadPercussion[y].wav.unknown1);
				outputCtlCounter += 4;

				tblOffsets[startPercussionInListing+y] = tblSizes;

				bool foundSameTbl = false;

				if (!foundSameTbl)
				{
					for (int z = 0; z < overallTblOffsets.size(); z++)
					{
						if (CompareTbls(&alBank->eadPercussion[y].wav, overallTblDataWaves[z]))
						{
							foundSameTbl = true;
							tblOffsets[startPercussionInListing+y] = overallTblOffsets[z];
							break;
						}
					}
				}

				if (!foundSameTbl)
				{	
					int loopEnd = alBank->count;
					for (int z = 0; z < loopEnd; z++)
					{
						if (alBank->inst[z]->sounds[0] != NULL)
						{
							if (alBank->inst[z]->sounds[0]->hasWavePrevious)
							{
								if (CompareTbls(&alBank->eadPercussion[y].wav, &alBank->inst[z]->sounds[0]->wavPrevious))
								{
									foundSameTbl = true;
									tblOffsets[startPercussionInListing+y] = tblOffsetsPrevious[z];
									break;
								}
							}
						}
					}
				}

				if (!foundSameTbl)
				{
					int loopEnd = alBank->count;
					for (int z = 0; z < loopEnd; z++)
					{
						if (alBank->inst[z]->sounds[0] != NULL)
						{
							if (CompareTbls(&alBank->eadPercussion[y].wav, &alBank->inst[z]->sounds[0]->wav))
							{
								foundSameTbl = true;
								tblOffsets[startPercussionInListing+y] = tblOffsets[z];
								break;
							}
						}
					}
				}

				if (!foundSameTbl)
				{
					int loopEnd = alBank->count;
					for (int z = 0; z < loopEnd; z++)
					{
						if (alBank->inst[z]->sounds[0] != NULL)
						{
							if (alBank->inst[z]->sounds[0]->hasWaveSecondary)
							{
								if (CompareTbls(&alBank->eadPercussion[y].wav, &alBank->inst[z]->sounds[0]->wavSecondary))
								{
									foundSameTbl = true;
									tblOffsets[startPercussionInListing+y] = tblOffsetsSecondary[z];
									break;
								}
							}
						}
					}
				}

				if (!foundSameTbl)
				{
					int startPercussionInListingNew = alBank->count;

					int loopEnd = y;
					for (int z = 0; z < loopEnd; z++)
					{
						if (CompareTbls(&alBank->eadPercussion[y].wav, &alBank->eadPercussion[z].wav))
						{
							foundSameTbl = true;
							tblOffsets[startPercussionInListing+y] = tblOffsets[startPercussionInListingNew+z];
							break;
						}
					}
				}

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, tblOffsets[startPercussionInListing+y]);
				outputCtlCounter += 4;


				if (!foundSameTbl)
				{
					overallTblOffsets.push_back(tblOffsets[startPercussionInListing+y]);
					overallTblDataWaves.push_back(&alBank->eadPercussion[y].wav);

					unsigned long curEntrySize = alBank->eadPercussion[y].wav.len;
					if ((alBank->eadPercussion[y].wav.len % 0x10) != 0)
						curEntrySize += (0x10 - (alBank->eadPercussion[y].wav.len % 0x10));

					for (int z = 0; z < alBank->eadPercussion[y].wav.len; z++)
					{
						tblData[tblSizes + z] = alBank->eadPercussion[y].wav.wavData[z];
					}

					tblSizes += curEntrySize;
					
					if ((tblSizes % 0x10) != 0)
					{
						tblSizes += (0x10 - (tblSizes % 0x10));
					}
				}

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, (adpcmRawLoopOffsetsWav[startPercussionInListing+y] - soundDataOffset));
				outputCtlCounter += 4;

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, (bookOffsetsWav[startPercussionInListing+y] - soundDataOffset));
				outputCtlCounter += 4;

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->eadPercussion[y].wav.len);
				outputCtlCounter += 4;

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->eadPercussion[y].wav.unknown2);
				outputCtlCounter += 4;

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->eadPercussion[y].wav.unknown3);
				outputCtlCounter += 4;

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->eadPercussion[y].wav.unknown4);
				outputCtlCounter += 4;

				if (sameBook == -1)
				{
					WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->eadPercussion[y].wav.adpcmWave->book->order);
					outputCtlCounter += 4;
					WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->eadPercussion[y].wav.adpcmWave->book->npredictors);
					outputCtlCounter += 4;

					for (int z = 0; z < (alBank->eadPercussion[y].wav.adpcmWave->book->order * alBank->eadPercussion[y].wav.adpcmWave->book->npredictors * 8); z++)
					{
						temporaryCtlBuffer[outputCtlCounter++] = ((alBank->eadPercussion[y].wav.adpcmWave->book->predictors[z] >> 8) & 0xFF);
						temporaryCtlBuffer[outputCtlCounter++] = ((alBank->eadPercussion[y].wav.adpcmWave->book->predictors[z]) & 0xFF);
					}

					if ((outputCtlCounter % 0x10) != 0)
						outputCtlCounter = outputCtlCounter + (0x10 - (outputCtlCounter % 0x10));
				}

				if (sameLoop == -1)
				{

					WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->eadPercussion[y].wav.adpcmWave->loop->start);
					outputCtlCounter += 4;
					WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->eadPercussion[y].wav.adpcmWave->loop->end);
					outputCtlCounter += 4;
					WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->eadPercussion[y].wav.adpcmWave->loop->count);
					outputCtlCounter += 4;
					WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->eadPercussion[y].wav.adpcmWave->loop->unknown1);
					outputCtlCounter += 4;

					if (alBank->eadPercussion[y].wav.adpcmWave->loop->start != 0)
					{
						for (int z = 0; z < 0x10; z++)
						{
							temporaryCtlBuffer[outputCtlCounter++] = ((alBank->eadPercussion[y].wav.adpcmWave->loop->state[z] >> 8) & 0xFF);
							temporaryCtlBuffer[outputCtlCounter++] = ((alBank->eadPercussion[y].wav.adpcmWave->loop->state[z]) & 0xFF);
						}
					}

					if ((outputCtlCounter % 0x10) != 0)
						outputCtlCounter = outputCtlCounter + (0x10 - (outputCtlCounter % 0x10));
				}
			}
		}

		for (int y = 0; y < alBank->count; y++)
		{
			offsetsEnv[y] = (outputCtlCounter - soundDataOffset);

			if (alBank->inst[y]->sounds[0] != NULL)
			{

				bool foundPast = false;

				for (int z = 0; z < y; z++)
				{
					if (alBank->inst[z]->sounds[0] != NULL)
					{
						if (
							(alBank->inst[y]->sounds[0]->adsrEAD[0] == alBank->inst[z]->sounds[0]->adsrEAD[0])
							&& (alBank->inst[y]->sounds[0]->adsrEAD[1] == alBank->inst[z]->sounds[0]->adsrEAD[1])
							&& (alBank->inst[y]->sounds[0]->adsrEAD[2] == alBank->inst[z]->sounds[0]->adsrEAD[2])
							&& (alBank->inst[y]->sounds[0]->adsrEAD[3] == alBank->inst[z]->sounds[0]->adsrEAD[3])
							&& (alBank->inst[y]->sounds[0]->adsrEAD[4] == alBank->inst[z]->sounds[0]->adsrEAD[4])
							&& (alBank->inst[y]->sounds[0]->adsrEAD[5] == alBank->inst[z]->sounds[0]->adsrEAD[5])
							&& (alBank->inst[y]->sounds[0]->adsrEAD[6] == alBank->inst[z]->sounds[0]->adsrEAD[6])
							&& (alBank->inst[y]->sounds[0]->adsrEAD[7] == alBank->inst[z]->sounds[0]->adsrEAD[7])
							)
						{
							foundPast = true;
							offsetsEnv[y] = offsetsEnv[z];
							break;
						}
					}
				}

				if (foundPast)
					continue;

				for (int z = 0; z < 8; z++)
				{
					WriteShortToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->adsrEAD[z]);
					outputCtlCounter += 2;
				}
			}
		}

		for (int y = 0; y < alBank->countEADPercussion; y++)
		{
			offsetsEnv[startPercussionInListing+y] = (outputCtlCounter - soundDataOffset);

			bool foundPast = false;

			for (int z = 0; z < alBank->count; z++)
			{
				if (alBank->inst[z]->sounds[0] != NULL)
				{
					if (
						(alBank->eadPercussion[y].adsrEAD[0] == alBank->inst[z]->sounds[0]->adsrEAD[0])
						&& (alBank->eadPercussion[y].adsrEAD[1] == alBank->inst[z]->sounds[0]->adsrEAD[1])
						&& (alBank->eadPercussion[y].adsrEAD[2] == alBank->inst[z]->sounds[0]->adsrEAD[2])
						&& (alBank->eadPercussion[y].adsrEAD[3] == alBank->inst[z]->sounds[0]->adsrEAD[3])
						&& (alBank->eadPercussion[y].adsrEAD[4] == alBank->inst[z]->sounds[0]->adsrEAD[4])
						&& (alBank->eadPercussion[y].adsrEAD[5] == alBank->inst[z]->sounds[0]->adsrEAD[5])
						&& (alBank->eadPercussion[y].adsrEAD[6] == alBank->inst[z]->sounds[0]->adsrEAD[6])
						&& (alBank->eadPercussion[y].adsrEAD[7] == alBank->inst[z]->sounds[0]->adsrEAD[7])
						)
					{
						foundPast = true;
						offsetsEnv[startPercussionInListing+y] = offsetsEnv[z];
						break;
					}
				}
			}

			if (foundPast)
				continue;

			for (int z = 0; z < y; z++)
			{
				if (
					(alBank->eadPercussion[y].adsrEAD[0] == alBank->eadPercussion[z].adsrEAD[0])
					&& (alBank->eadPercussion[y].adsrEAD[1] == alBank->eadPercussion[z].adsrEAD[1])
					&& (alBank->eadPercussion[y].adsrEAD[2] == alBank->eadPercussion[z].adsrEAD[2])
					&& (alBank->eadPercussion[y].adsrEAD[3] == alBank->eadPercussion[z].adsrEAD[3])
					&& (alBank->eadPercussion[y].adsrEAD[4] == alBank->eadPercussion[z].adsrEAD[4])
					&& (alBank->eadPercussion[y].adsrEAD[5] == alBank->eadPercussion[z].adsrEAD[5])
					&& (alBank->eadPercussion[y].adsrEAD[6] == alBank->eadPercussion[z].adsrEAD[6])
					&& (alBank->eadPercussion[y].adsrEAD[7] == alBank->eadPercussion[z].adsrEAD[7])
					)
				{
					foundPast = true;
					offsetsEnv[startPercussionInListing+y] = offsetsEnv[startPercussionInListing+z];
					break;
				}
			}

			if (foundPast)
				continue;

			for (int z = 0; z < 8; z++)
			{
				WriteShortToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->eadPercussion[y].adsrEAD[z]);
				outputCtlCounter += 2;
			}
		}

		for (int y = 0; y < alBank->count; y++)
		{
			if (alBank->inst[y]->sounds[0] != NULL)
			{
				WriteLongToBuffer(temporaryCtlBuffer, soundOffsetSpot + (y * 0x4), (outputCtlCounter - soundDataOffset));

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->unknown1);
				outputCtlCounter += 4;

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, offsetsEnv[y]);
				outputCtlCounter += 4;

				if (alBank->inst[y]->sounds[0]->hasWavePrevious)
				{
					WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, offsetsWavPrevious[y]);
					outputCtlCounter += 4;
				}
				else
				{
					WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, 0x00000000);
					outputCtlCounter += 4;
				}

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->floatKeyBasePrev);
				outputCtlCounter += 4;

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, offsetsWav[y]);
				outputCtlCounter += 4;

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->floatKeyBase);
				outputCtlCounter += 4;

				if (alBank->inst[y]->sounds[0]->hasWaveSecondary)
				{
					WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, offsetsWavSecondary[y]);
					outputCtlCounter += 4;
				}
				else
				{
					WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, 0x00000000);
					outputCtlCounter += 4;
				}

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->sounds[0]->floatKeyBaseSec);
				outputCtlCounter += 4;
			}
			else
			{
				WriteLongToBuffer(temporaryCtlBuffer, soundOffsetSpot + (y * 0x4), 0x00000000);
			}
		}

		if ((outputCtlCounter % 0x10) != 0)
			outputCtlCounter += (0x10 - (outputCtlCounter % 0x10));

		

		if (alBank->countEADPercussion == 0)
		{
			WriteLongToBuffer(temporaryCtlBuffer, soundDataOffset, 0x00000000);
		}
		else
		{
			unsigned long startPercussionDataOffsets = (outputCtlCounter  - soundDataOffset);
			for (int y = 0; y < alBank->countEADPercussion; y++)
			{
				temporaryCtlBuffer[outputCtlCounter] = alBank->eadPercussion[y].unknown1A;
				outputCtlCounter++;

				temporaryCtlBuffer[outputCtlCounter] = alBank->eadPercussion[y].pan;
				outputCtlCounter++;

				WriteShortToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->eadPercussion[y].unknown1C);
				outputCtlCounter += 2;

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, offsetsWav[alBank->count + y]);
				outputCtlCounter += 4;

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->eadPercussion[y].keyBase);
				outputCtlCounter += 4;

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, offsetsEnv[alBank->count + y]);
				outputCtlCounter += 4;
			}

			if ((outputCtlCounter % 0x10) != 0)
				outputCtlCounter += (0x10 - (outputCtlCounter % 0x10));

			WriteLongToBuffer(temporaryCtlBuffer, soundDataOffset, (outputCtlCounter  - soundDataOffset));

			for (int y = 0; y < alBank->countEADPercussion; y++)
			{
				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, startPercussionDataOffsets + (y * 0x10));
				outputCtlCounter += 4;
			}

			if ((outputCtlCounter % 0x10) != 0)
				outputCtlCounter += (0x10 - (outputCtlCounter % 0x10));
		}

		// ctl bank size
		WriteLongToBuffer(temporaryCtlBuffer, 0x4 + (0x8 * soundBankNumber) + 0x4, (outputCtlCounter - instrumentALLookup));

		delete [] instrumentSoundStartLookup;
		delete [] offsetsEnv;
		delete [] offsetsWav;
		delete [] bookOffsetsWav;
		delete [] adpcmRawLoopOffsetsWav;
		delete [] tblOffsets;

		delete [] offsetsWavSecondary;
		delete [] bookOffsetsWavSecondary;
		delete [] adpcmRawLoopOffsetsWavSecondary;
		delete [] tblOffsetsSecondary;

		delete [] offsetsWavPrevious;
		delete [] bookOffsetsWavPrevious;
		delete [] adpcmRawLoopOffsetsWavPrevious;
		delete [] tblOffsetsPrevious;
	}

	unsigned long outputTblCounter = 0;

	WriteShortToBuffer(temporaryTblBuffer, outputTblCounter, 0x0002);
	outputTblCounter += 2;

	WriteShortToBuffer(temporaryTblBuffer, outputTblCounter, results.size());
	outputTblCounter += 2;

	for (int x = 0; x < results.size(); x++)
	{
		// offset to bank later in file
		outputTblCounter += 8;
	}

	if ((outputTblCounter % 0x10) != 0)
		outputTblCounter += ((0x10 - (outputTblCounter % 0x10)));

	//outputTblCounter = (4 + (soundBankNumber * 8));

	unsigned long endTblHeader = outputTblCounter;

	memcpy(&temporaryTblBuffer[outputTblCounter], tblData, tblSizes);

	outputTblCounter += tblSizes;

	if ((outputTblCounter % 0x10) != 0)
		outputTblCounter += ((0x10 - (outputTblCounter % 0x10)));

	for (int x = 0; x < results.size(); x++)
	{
		WriteLongToBuffer(temporaryTblBuffer, 0x4 + (x * 0x8), endTblHeader);
		WriteLongToBuffer(temporaryTblBuffer, 0x4 + (x * 0x8) + 0x4, tblSizes);
	}


	delete[] tblData;

	
	
	ctl = temporaryCtlBuffer;
	tbl = temporaryTblBuffer;

	ctlSize = outputCtlCounter;
	tblSize = outputTblCounter;
}

void CN64AIFCAudio::WriteAudio(ALBank*& alBank, unsigned char*& ctl, int& ctlSize, unsigned char*& tbl, int& tblSize)
{
	unsigned char* temporaryCtlBuffer = new unsigned char[0x1000000];
	unsigned char* temporaryTblBuffer = new unsigned char[0x1000000];
	unsigned long outputCtlCounter = 0;
	
	// magic
	WriteShortToBuffer(temporaryCtlBuffer, outputCtlCounter, 0x4231);
	outputCtlCounter += 2;

	// bank #
	int bankCount = 1;
	WriteShortToBuffer(temporaryCtlBuffer, outputCtlCounter, bankCount);
	outputCtlCounter += 2;

	for (int x = 0; x < bankCount; x++)
	{
		// offset to bank later in file
		outputCtlCounter += 4;
	}

	unsigned long outputTblCounter = 0;

	unsigned long percussionALLookup = 0;	
	unsigned long* percussioninstrumentSoundStartLookup = NULL;
	unsigned long* percussionoffsetsEnv = NULL;
	unsigned long* percussionoffsetsKey = NULL;
	unsigned long* percussionoffsetsWav = NULL;
	unsigned long* percussionbookOffsetsWav = NULL;
	unsigned long* percussionadpcmRawLoopOffsetsWav = NULL;
	unsigned long* percussionrawLoopOffsetsWav = NULL;
	unsigned long* percussiontblOffsets = NULL;

	if (alBank->percussion != NULL)
	{
		percussioninstrumentSoundStartLookup = new unsigned long[alBank->percussion->soundCount];
		percussionoffsetsEnv = new unsigned long[alBank->percussion->soundCount];
		percussionoffsetsKey = new unsigned long[alBank->percussion->soundCount];
		percussionoffsetsWav = new unsigned long[alBank->percussion->soundCount];
		percussionbookOffsetsWav = new unsigned long[alBank->percussion->soundCount];
		percussionadpcmRawLoopOffsetsWav = new unsigned long[alBank->percussion->soundCount];
		percussionrawLoopOffsetsWav = new unsigned long[alBank->percussion->soundCount];
		percussiontblOffsets = new unsigned long[alBank->percussion->soundCount];
	}


	unsigned long* instrumentALLookup = new unsigned long[alBank->count];
	unsigned long** instrumentSoundStartLookup = new unsigned long*[alBank->count];
	unsigned long** offsetsEnv = new unsigned long*[alBank->count];
	unsigned long** offsetsKey = new unsigned long*[alBank->count];
	unsigned long** offsetsWav = new unsigned long*[alBank->count];
	unsigned long** bookOffsetsWav = new unsigned long*[alBank->count];
	unsigned long** adpcmRawLoopOffsetsWav = new unsigned long*[alBank->count];
	unsigned long** rawLoopOffsetsWav = new unsigned long*[alBank->count];
	unsigned long** tblOffsets = new unsigned long*[alBank->count];

	for (int x = 0; x < alBank->count; x++)
	{
		instrumentSoundStartLookup[x] = new unsigned long[alBank->inst[x]->soundCount];
		offsetsEnv[x] = new unsigned long[alBank->inst[x]->soundCount];
		offsetsKey[x] = new unsigned long[alBank->inst[x]->soundCount];
		offsetsWav[x] = new unsigned long[alBank->inst[x]->soundCount];
		bookOffsetsWav[x] = new unsigned long[alBank->inst[x]->soundCount];
		adpcmRawLoopOffsetsWav[x] = new unsigned long[alBank->inst[x]->soundCount];
		rawLoopOffsetsWav[x] = new unsigned long[alBank->inst[x]->soundCount];
		tblOffsets[x] = new unsigned long[alBank->inst[x]->soundCount];
	}

	if (alBank->percussion != NULL)
	{
		unsigned long envStart = outputCtlCounter;

		for (int y = 0; y < alBank->percussion->soundCount; y++)
		{
			bool foundPast = false;

			int loopEnd = y;
			
			for (int z = 0; z < loopEnd; z++)
			{
				if (
					(alBank->percussion->sounds[y]->env.attackTime == alBank->percussion->sounds[z]->env.attackTime)
					&& (alBank->percussion->sounds[y]->env.decayTime == alBank->percussion->sounds[z]->env.decayTime)
					&& (alBank->percussion->sounds[y]->env.releaseTime == alBank->percussion->sounds[z]->env.releaseTime)
					&& (alBank->percussion->sounds[y]->env.attackVolume == alBank->percussion->sounds[z]->env.attackVolume)
					&& (alBank->percussion->sounds[y]->env.decayVolume == alBank->percussion->sounds[z]->env.decayVolume)
					)
				{
					foundPast = true;
					percussionoffsetsEnv[y] = percussionoffsetsEnv[z];
					break;
				}
			}

			if (foundPast)
				continue;

			percussionoffsetsEnv[y] = outputCtlCounter;

			WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->percussion->sounds[y]->env.attackTime);
			outputCtlCounter += 4;
			WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->percussion->sounds[y]->env.decayTime);
			outputCtlCounter += 4;
			WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->percussion->sounds[y]->env.releaseTime);
			outputCtlCounter += 4;
			temporaryCtlBuffer[outputCtlCounter] = alBank->percussion->sounds[y]->env.attackVolume;
			outputCtlCounter += 1;
			temporaryCtlBuffer[outputCtlCounter] = alBank->percussion->sounds[y]->env.decayVolume;
			outputCtlCounter += 1;
			WriteShortToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->percussion->sounds[y]->env.zeroPad);
			outputCtlCounter += 2;
		}
	}

	for (int x = 0; x < alBank->count; x++)
	{
		unsigned long envStart = outputCtlCounter;
		for (int y = 0; y < alBank->inst[x]->soundCount; y++)
		{
			bool foundPast = false;

			if (alBank->percussion != NULL)
			{
				for (int z = 0; z < alBank->percussion->soundCount; z++)
				{
					if (
						(alBank->inst[x]->sounds[y]->env.attackTime == alBank->percussion->sounds[z]->env.attackTime)
						&& (alBank->inst[x]->sounds[y]->env.decayTime == alBank->percussion->sounds[z]->env.decayTime)
						&& (alBank->inst[x]->sounds[y]->env.releaseTime == alBank->percussion->sounds[z]->env.releaseTime)
						&& (alBank->inst[x]->sounds[y]->env.attackVolume == alBank->percussion->sounds[z]->env.attackVolume)
						&& (alBank->inst[x]->sounds[y]->env.decayVolume == alBank->percussion->sounds[z]->env.decayVolume)
						)
					{
						foundPast = true;
						offsetsEnv[x][y] = percussionoffsetsEnv[z];
						break;
					}
				}

				if (foundPast)
					continue;
			}

			for (int r = 0; r < (x + 1); r++)
			{
				int loopEnd = y;
				if (r != x)
				{
					loopEnd = alBank->inst[r]->soundCount;
				}
				for (int z = 0; z < loopEnd; z++)
				{
					if (
						(alBank->inst[x]->sounds[y]->env.attackTime == alBank->inst[r]->sounds[z]->env.attackTime)
						&& (alBank->inst[x]->sounds[y]->env.decayTime == alBank->inst[r]->sounds[z]->env.decayTime)
						&& (alBank->inst[x]->sounds[y]->env.releaseTime == alBank->inst[r]->sounds[z]->env.releaseTime)
						&& (alBank->inst[x]->sounds[y]->env.attackVolume == alBank->inst[r]->sounds[z]->env.attackVolume)
						&& (alBank->inst[x]->sounds[y]->env.decayVolume == alBank->inst[r]->sounds[z]->env.decayVolume)
						)
					{
						foundPast = true;
						offsetsEnv[x][y] = offsetsEnv[r][z];
						break;
					}
				}
			}

			/*if (y != 0)
			{
				//hack
				offsetsEnv[x][y] = offsetsEnv[0][0];
				foundPast = true;
			}*/


			if (foundPast)
				continue;

			offsetsEnv[x][y] = outputCtlCounter;

			WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->env.attackTime);
			outputCtlCounter += 4;
			WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->env.decayTime);
			outputCtlCounter += 4;
			WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->env.releaseTime);
			outputCtlCounter += 4;
			temporaryCtlBuffer[outputCtlCounter] = alBank->inst[x]->sounds[y]->env.attackVolume;
			outputCtlCounter += 1;
			temporaryCtlBuffer[outputCtlCounter] = alBank->inst[x]->sounds[y]->env.decayVolume;
			outputCtlCounter += 1;
			WriteShortToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->env.zeroPad);
			outputCtlCounter += 2;
		}
	}

	if (alBank->percussion != NULL)
	{
		if ((outputCtlCounter % 0x10) != 0)
		{
			outputCtlCounter = outputCtlCounter + (0x10 - (outputCtlCounter % 0x10));
		}

		unsigned long keyStart = outputCtlCounter;
		for (int y = 0; y < alBank->percussion->soundCount; y++)
		{
			bool foundPast = false;

			int loopEnd = y;
			
			for (int z = 0; z < loopEnd; z++)
			{
				if (
					(alBank->percussion->sounds[y]->key.velocitymin == alBank->percussion->sounds[z]->key.velocitymin)
					&& (alBank->percussion->sounds[y]->key.velocitymax == alBank->percussion->sounds[z]->key.velocitymax)
					&& (alBank->percussion->sounds[y]->key.keymin == alBank->percussion->sounds[z]->key.keymin)
					&& (alBank->percussion->sounds[y]->key.keymax == alBank->percussion->sounds[z]->key.keymax)
					&& (alBank->percussion->sounds[y]->key.keybase == alBank->percussion->sounds[z]->key.keybase)
					&& (alBank->percussion->sounds[y]->key.detune == alBank->percussion->sounds[z]->key.detune)
					)
				{
					foundPast = true;
					percussionoffsetsKey[y] = percussionoffsetsKey[z];
					break;
				}
			}

			if (foundPast)
				continue;


			percussionoffsetsKey[y] = outputCtlCounter;

			temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->sounds[y]->key.velocitymin;
			temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->sounds[y]->key.velocitymax;
			temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->sounds[y]->key.keymin;
			temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->sounds[y]->key.keymax;
			temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->sounds[y]->key.keybase;
			temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->sounds[y]->key.detune;

			if ((outputCtlCounter % 8) != 0)
			{
				int pad = 8 - (outputCtlCounter % 8);
				for (int z = 0; z < pad; z++)
				{
					temporaryCtlBuffer[outputCtlCounter++] = 0;
				}
			}
		}


		if ((outputCtlCounter % 8) != 0)
		{
			int pad = 8 - (outputCtlCounter % 8);
			for (int z = 0; z < pad; z++)
			{
				temporaryCtlBuffer[outputCtlCounter++] = 0;
			}
		}
	}

	for (int x = 0; x < alBank->count; x++)
	{
		if ((outputCtlCounter % 0x10) != 0)
		{
			outputCtlCounter = outputCtlCounter + (0x10 - (outputCtlCounter % 0x10));
		}

		unsigned long keyStart = outputCtlCounter;
		for (int y = 0; y < alBank->inst[x]->soundCount; y++)
		{
			bool foundPast = false;

			if (alBank->percussion != NULL)
			{
				for (int z = 0; z < alBank->percussion->soundCount; z++)
				{
					if (
						(alBank->inst[x]->sounds[y]->key.velocitymin == alBank->percussion->sounds[z]->key.velocitymin)
						&& (alBank->inst[x]->sounds[y]->key.velocitymax == alBank->percussion->sounds[z]->key.velocitymax)
						&& (alBank->inst[x]->sounds[y]->key.keymin == alBank->percussion->sounds[z]->key.keymin)
						&& (alBank->inst[x]->sounds[y]->key.keymax == alBank->percussion->sounds[z]->key.keymax)
						&& (alBank->inst[x]->sounds[y]->key.keybase == alBank->percussion->sounds[z]->key.keybase)
						&& (alBank->inst[x]->sounds[y]->key.detune == alBank->percussion->sounds[z]->key.detune)
						)
					{
						foundPast = true;
						offsetsKey[x][y] = percussionoffsetsKey[z];
						break;
					}
				}

				if (foundPast)
					continue;
			}

			for (int r = 0; r < (x + 1); r++)
			{
				int loopEnd = y;
				if (r != x)
				{
					loopEnd = alBank->inst[r]->soundCount;
				}
				for (int z = 0; z < loopEnd; z++)
				{
					if (
						(alBank->inst[x]->sounds[y]->key.velocitymin == alBank->inst[r]->sounds[z]->key.velocitymin)
						&& (alBank->inst[x]->sounds[y]->key.velocitymax == alBank->inst[r]->sounds[z]->key.velocitymax)
						&& (alBank->inst[x]->sounds[y]->key.keymin == alBank->inst[r]->sounds[z]->key.keymin)
						&& (alBank->inst[x]->sounds[y]->key.keymax == alBank->inst[r]->sounds[z]->key.keymax)
						&& (alBank->inst[x]->sounds[y]->key.keybase == alBank->inst[r]->sounds[z]->key.keybase)
						&& (alBank->inst[x]->sounds[y]->key.detune == alBank->inst[r]->sounds[z]->key.detune)
						)
					{
						foundPast = true;
						offsetsKey[x][y] = offsetsKey[r][z];
						break;
					}
				}
			}

			if (foundPast)
				continue;


			offsetsKey[x][y] = outputCtlCounter;

			temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[x]->sounds[y]->key.velocitymin;
			temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[x]->sounds[y]->key.velocitymax;
			temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[x]->sounds[y]->key.keymin;
			temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[x]->sounds[y]->key.keymax;
			temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[x]->sounds[y]->key.keybase;
			temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[x]->sounds[y]->key.detune;

			if ((outputCtlCounter % 8) != 0)
			{
				int pad = 8 - (outputCtlCounter % 8);
				for (int z = 0; z < pad; z++)
				{
					temporaryCtlBuffer[outputCtlCounter++] = 0;
				}
			}
		}


		if ((outputCtlCounter % 8) != 0)
		{
			int pad = 8 - (outputCtlCounter % 8);
			for (int z = 0; z < pad; z++)
			{
				temporaryCtlBuffer[outputCtlCounter++] = 0;
			}
		}
	}

	if (alBank->percussion != NULL)
	{
		unsigned long wavStart = outputCtlCounter;

		for (int y = 0; y < alBank->percussion->soundCount; y++)
		{
			percussioninstrumentSoundStartLookup[y] = outputCtlCounter;

			percussionoffsetsWav[y] = outputCtlCounter + 0x10;

			bool entireSoundMatch = false;

			int entireMatch = -1;
			
			int loopEnd = y;
			
			for (int w = 0; w < loopEnd; w++)
			{
				if (
					(alBank->percussion->sounds[y]->wav.base == alBank->percussion->sounds[w]->wav.base)
					&& (alBank->percussion->sounds[y]->wav.len == alBank->percussion->sounds[w]->wav.len)
					&& (alBank->percussion->sounds[y]->wav.flags == alBank->percussion->sounds[w]->wav.flags)
					&& (alBank->percussion->sounds[y]->wav.type == alBank->percussion->sounds[w]->wav.type)
					)
				{
					if (alBank->percussion->sounds[y]->wav.type == 0)
					{
						if (((alBank->percussion->sounds[y]->wav.adpcmWave->loop == NULL) && (alBank->percussion->sounds[w]->wav.adpcmWave->loop != NULL))
							|| ((alBank->percussion->sounds[y]->wav.adpcmWave->loop != NULL) && (alBank->percussion->sounds[w]->wav.adpcmWave->loop == NULL)))
						{
							continue;
						}

						bool sameLoop = false;
						if ((alBank->percussion->sounds[y]->wav.adpcmWave->loop == NULL) && (alBank->percussion->sounds[w]->wav.adpcmWave->loop == NULL))
						{
							sameLoop = true;
						}
						else
						{
							if (
								(alBank->percussion->sounds[y]->wav.adpcmWave->loop->start == alBank->percussion->sounds[w]->wav.adpcmWave->loop->start)
								&& (alBank->percussion->sounds[y]->wav.adpcmWave->loop->end == alBank->percussion->sounds[w]->wav.adpcmWave->loop->end)
								&& (alBank->percussion->sounds[y]->wav.adpcmWave->loop->count == alBank->percussion->sounds[w]->wav.adpcmWave->loop->count))
							{
								bool abort = false;
								for (int z = 0; z < 0x10; z++)
								{
									if (alBank->percussion->sounds[y]->wav.adpcmWave->loop->state[z] != alBank->percussion->sounds[w]->wav.adpcmWave->loop->state[z])
									{
										abort = true;
										break;
									}
								}

								if (abort)
									continue;
								else

									sameLoop = true;
							}
							else
							{
								continue;
							}
						}

						if (sameLoop)
						{
							if ((alBank->percussion->sounds[y]->wav.adpcmWave->book->npredictors == alBank->percussion->sounds[w]->wav.adpcmWave->book->npredictors)
								&& (alBank->percussion->sounds[y]->wav.adpcmWave->book->order == alBank->percussion->sounds[w]->wav.adpcmWave->book->order))
							{
								bool abort = false;
								for (int z = 0; z < (alBank->percussion->sounds[y]->wav.adpcmWave->book->npredictors * alBank->percussion->sounds[y]->wav.adpcmWave->book->order * 8); z++)
								{
									if (alBank->percussion->sounds[y]->wav.adpcmWave->book->predictors[z] != alBank->percussion->sounds[w]->wav.adpcmWave->book->predictors[z])
									{
										abort = true;
										break;
									}
								}

								if (abort)
									continue;
								else
								{
									entireMatch = w;
									percussionoffsetsWav[y] = percussionoffsetsWav[entireMatch];
									percussionbookOffsetsWav[y] = percussionbookOffsetsWav[entireMatch];
									percussiontblOffsets[y] = percussiontblOffsets[entireMatch];


									if (
										(alBank->percussion->sounds[y]->env.attackTime == alBank->percussion->sounds[entireMatch]->env.attackTime)
										&& (alBank->percussion->sounds[y]->env.attackVolume == alBank->percussion->sounds[entireMatch]->env.attackVolume)
										&& (alBank->percussion->sounds[y]->env.decayTime == alBank->percussion->sounds[entireMatch]->env.decayTime)
										&& (alBank->percussion->sounds[y]->env.decayVolume == alBank->percussion->sounds[entireMatch]->env.decayVolume)
										&& (alBank->percussion->sounds[y]->env.releaseTime == alBank->percussion->sounds[entireMatch]->env.releaseTime)
										&& (alBank->percussion->sounds[y]->samplePan == alBank->percussion->sounds[entireMatch]->samplePan)
										&& (alBank->percussion->sounds[y]->sampleVolume == alBank->percussion->sounds[entireMatch]->sampleVolume)
										&& (alBank->percussion->sounds[y]->flags == alBank->percussion->sounds[entireMatch]->flags)
										&& (alBank->percussion->sounds[y]->key.detune == alBank->percussion->sounds[entireMatch]->key.detune)
										&& (alBank->percussion->sounds[y]->key.keybase == alBank->percussion->sounds[entireMatch]->key.keybase)
										&& (alBank->percussion->sounds[y]->key.keymax == alBank->percussion->sounds[entireMatch]->key.keymax)
										&& (alBank->percussion->sounds[y]->key.keymin == alBank->percussion->sounds[entireMatch]->key.keymin)
										&& (alBank->percussion->sounds[y]->key.velocitymax == alBank->percussion->sounds[entireMatch]->key.velocitymax)
										&& (alBank->percussion->sounds[y]->key.velocitymin == alBank->percussion->sounds[entireMatch]->key.velocitymin)
										)
									{
										percussioninstrumentSoundStartLookup[y] = percussioninstrumentSoundStartLookup[entireMatch];
										entireSoundMatch = true;
										break;
									}
									else
									{
										continue;
									}
									
								}
							}
							else
							{
								continue;
							}
						}
					}
					else
					{
						if (((alBank->percussion->sounds[y]->wav.rawWave->loop == NULL) && (alBank->percussion->sounds[w]->wav.rawWave->loop != NULL))
							|| ((alBank->percussion->sounds[y]->wav.rawWave->loop != NULL) && (alBank->percussion->sounds[w]->wav.rawWave->loop == NULL)))
						{
							continue;
						}

						bool sameLoop = false;
						if ((alBank->percussion->sounds[y]->wav.rawWave->loop == NULL) && (alBank->percussion->sounds[w]->wav.rawWave->loop == NULL))
						{
							sameLoop = true;
						}
						else
						{
							if (
								(alBank->percussion->sounds[y]->wav.rawWave->loop->start == alBank->percussion->sounds[w]->wav.rawWave->loop->start)
								&& (alBank->percussion->sounds[y]->wav.rawWave->loop->end == alBank->percussion->sounds[w]->wav.rawWave->loop->end)
								&& (alBank->percussion->sounds[y]->wav.rawWave->loop->count == alBank->percussion->sounds[w]->wav.rawWave->loop->count))
							{
								entireMatch = w;
								percussionoffsetsWav[y] = percussionoffsetsWav[entireMatch];
								percussionbookOffsetsWav[y] = percussionbookOffsetsWav[entireMatch];
								percussiontblOffsets[y] = percussiontblOffsets[entireMatch];
								
								if (
										(alBank->percussion->sounds[y]->env.attackTime == alBank->percussion->sounds[entireMatch]->env.attackTime)
										&& (alBank->percussion->sounds[y]->env.attackVolume == alBank->percussion->sounds[entireMatch]->env.attackVolume)
										&& (alBank->percussion->sounds[y]->env.decayTime == alBank->percussion->sounds[entireMatch]->env.decayTime)
										&& (alBank->percussion->sounds[y]->env.decayVolume == alBank->percussion->sounds[entireMatch]->env.decayVolume)
										&& (alBank->percussion->sounds[y]->env.releaseTime == alBank->percussion->sounds[entireMatch]->env.releaseTime)
										&& (alBank->percussion->sounds[y]->samplePan == alBank->percussion->sounds[entireMatch]->samplePan)
										&& (alBank->percussion->sounds[y]->sampleVolume == alBank->percussion->sounds[entireMatch]->sampleVolume)
										&& (alBank->percussion->sounds[y]->flags == alBank->percussion->sounds[entireMatch]->flags)
										&& (alBank->percussion->sounds[y]->key.detune == alBank->percussion->sounds[entireMatch]->key.detune)
										&& (alBank->percussion->sounds[y]->key.keybase == alBank->percussion->sounds[entireMatch]->key.keybase)
										&& (alBank->percussion->sounds[y]->key.keymax == alBank->percussion->sounds[entireMatch]->key.keymax)
										&& (alBank->percussion->sounds[y]->key.keymin == alBank->percussion->sounds[entireMatch]->key.keymin)
										&& (alBank->percussion->sounds[y]->key.velocitymax == alBank->percussion->sounds[entireMatch]->key.velocitymax)
										&& (alBank->percussion->sounds[y]->key.velocitymin == alBank->percussion->sounds[entireMatch]->key.velocitymin)
										)
									{
										percussioninstrumentSoundStartLookup[y] = percussioninstrumentSoundStartLookup[entireMatch];
										entireSoundMatch = true;
										break;
									}
									else
									{
										continue;
									}
							}
							else
							{
								continue;
							}
						}
					}
				}
			}

			

			if (!entireSoundMatch)
			{
				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, percussionoffsetsEnv[y]);
				outputCtlCounter += 4;
				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, percussionoffsetsKey[y]);
				outputCtlCounter += 4;

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, percussionoffsetsWav[y]);
				outputCtlCounter += 4;

				temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->sounds[y]->samplePan;
				temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->sounds[y]->sampleVolume;
				WriteShortToBuffer(temporaryCtlBuffer, outputCtlCounter, 0);
				outputCtlCounter += 2;
			}

			if (entireMatch == -1)
			{
			
				percussiontblOffsets[y] = outputTblCounter;

				int foundSameTbl = false;

				int loopEnd = y;
					
				for (int z = 0; z < loopEnd; z++)
				{
					if (
						(alBank->percussion->sounds[y]->wav.base == alBank->percussion->sounds[z]->wav.base)
						&& (alBank->percussion->sounds[y]->wav.len == alBank->percussion->sounds[z]->wav.len)
						)
					{
						bool mismatchValues = false;
						for (int rr = 0; rr < alBank->percussion->sounds[y]->wav.len; rr++)
						{
							if (alBank->percussion->sounds[y]->wav.wavData[rr] != alBank->percussion->sounds[z]->wav.wavData[rr])
							{
								mismatchValues = true;
								break;
							}
						}
						if (!mismatchValues)
						{
							foundSameTbl = true;
							percussiontblOffsets[y] = percussiontblOffsets[z];
							break;
						}
						else
						{
							continue;
						}
					}
				}

				// update base
				//alBank->percussion->sounds[y]->wav.base = percussiontblOffsets[x][y];

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, percussiontblOffsets[y]);
				outputCtlCounter += 4;
				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->percussion->sounds[y]->wav.len);
				outputCtlCounter += 4;

				if (!foundSameTbl)
				{
					for (int z = 0; z < alBank->percussion->sounds[y]->wav.len; z++)
					{
						temporaryTblBuffer[outputTblCounter + z] = alBank->percussion->sounds[y]->wav.wavData[z];
					}
					outputTblCounter += alBank->percussion->sounds[y]->wav.len;

					if ((outputTblCounter % 8) != 0)
					{
						int pad = 8 - (outputTblCounter % 8);
						for (int z = 0; z < pad; z++)
						{
							temporaryTblBuffer[outputTblCounter++] = 0;
						}
					}
				}

				temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->sounds[y]->wav.type;
				temporaryCtlBuffer[outputCtlCounter++] = 0; // offset type
				temporaryCtlBuffer[outputCtlCounter++] = 0; // pad
				temporaryCtlBuffer[outputCtlCounter++] = 0; // pad

				if (alBank->percussion->sounds[y]->wav.type == AL_ADPCM_WAVE)
				{
					int sameLoop = -1;


					if (alBank->percussion->sounds[y]->wav.adpcmWave->loop != NULL)
					{
						if (sameLoop != -1)
							break;

						int loopEnd = y;
						
						for (int w = 0; w < loopEnd; w++)
						{
							if ((alBank->percussion->sounds[w]->wav.adpcmWave != NULL) && (alBank->percussion->sounds[w]->wav.adpcmWave->loop != NULL))
							{
								if ((alBank->percussion->sounds[y]->wav.adpcmWave->loop->start == alBank->percussion->sounds[w]->wav.adpcmWave->loop->start) 
									&& (alBank->percussion->sounds[y]->wav.adpcmWave->loop->end == alBank->percussion->sounds[w]->wav.adpcmWave->loop->end)
									&& (alBank->percussion->sounds[y]->wav.adpcmWave->loop->count == alBank->percussion->sounds[w]->wav.adpcmWave->loop->count))
								{
									bool goOn = false;
									for (int ww = 0; ww < 0x10; ww++)
									{
										if (alBank->percussion->sounds[w]->wav.adpcmWave->loop->state[ww] != alBank->percussion->sounds[y]->wav.adpcmWave->loop->state[ww])
										{
											goOn = true;
											break;
										}
									}

									if (goOn)
										continue;

									percussionadpcmRawLoopOffsetsWav[y] = percussionadpcmRawLoopOffsetsWav[w];
									sameLoop = w;
									break;
								}
							}
						}
					}

					unsigned long loopWriteSpot = outputCtlCounter;
					unsigned long bookWriteSpot = outputCtlCounter + 4;
					 
					int same = -1;
					
					if (same != -1)
						break;

					int loopEnd = y;
					
					for (int w = 0; w < loopEnd; w++)
					{
						if (alBank->percussion->sounds[w]->wav.adpcmWave != NULL)
						{
							if ((alBank->percussion->sounds[y]->wav.adpcmWave->book->order == alBank->percussion->sounds[w]->wav.adpcmWave->book->order) 
								&& (alBank->percussion->sounds[y]->wav.adpcmWave->book->npredictors == alBank->percussion->sounds[w]->wav.adpcmWave->book->npredictors))
							{
								bool goOn = false;
								for (int ww = 0; ww < (alBank->percussion->sounds[y]->wav.adpcmWave->book->order * alBank->percussion->sounds[y]->wav.adpcmWave->book->npredictors * 8); ww++)
								{
									if (alBank->percussion->sounds[w]->wav.adpcmWave->book->predictors[ww] != alBank->percussion->sounds[y]->wav.adpcmWave->book->predictors[ww])
									{
										goOn = true;
										break;
									}
								}

								if (goOn)
									continue;

								same = w;
								break;
							}
						}
					}

					// write later loop/predictor offsets
					outputCtlCounter += 8;


					if ((outputCtlCounter % 8) != 0)
					{
						int pad = 8 - (outputCtlCounter % 8);
						for (int z = 0; z < pad; z++)
						{
							temporaryCtlBuffer[outputCtlCounter++] = 0;
						}
					}

					if (alBank->percussion->sounds[y]->wav.adpcmWave->loop != NULL)
					{
						if (sameLoop == -1)
						{
							percussionadpcmRawLoopOffsetsWav[y] = outputCtlCounter;
							WriteLongToBuffer(temporaryCtlBuffer, loopWriteSpot, outputCtlCounter);

							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->percussion->sounds[y]->wav.adpcmWave->loop->start);
							outputCtlCounter += 4;
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->percussion->sounds[y]->wav.adpcmWave->loop->end);
							outputCtlCounter += 4;
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->percussion->sounds[y]->wav.adpcmWave->loop->count);
							outputCtlCounter += 4;
							for (int z = 0; z < 0x10; z++)
							{
								temporaryCtlBuffer[outputCtlCounter++] = ((alBank->percussion->sounds[y]->wav.adpcmWave->loop->state[z] >> 8) & 0xFF);
								temporaryCtlBuffer[outputCtlCounter++] = ((alBank->percussion->sounds[y]->wav.adpcmWave->loop->state[z]) & 0xFF);
							}
						}
						else
						{
							WriteLongToBuffer(temporaryCtlBuffer, loopWriteSpot, percussionadpcmRawLoopOffsetsWav[sameLoop]);
						}
					}
					else
					{
						// null loop
						WriteLongToBuffer(temporaryCtlBuffer, loopWriteSpot, 0x0);
					}

					if ((outputCtlCounter % 8) != 0)
					{
						int pad = 8 - (outputCtlCounter % 8);
						for (int z = 0; z < pad; z++)
						{
							temporaryCtlBuffer[outputCtlCounter++] = 0;
						}
					}

					if (same == -1)
					{
						percussionbookOffsetsWav[y] = outputCtlCounter;
						WriteLongToBuffer(temporaryCtlBuffer, bookWriteSpot, outputCtlCounter);

						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->percussion->sounds[y]->wav.adpcmWave->book->order);
						outputCtlCounter += 4;
						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->percussion->sounds[y]->wav.adpcmWave->book->npredictors);
						outputCtlCounter += 4;

						for (int z = 0; z < (alBank->percussion->sounds[y]->wav.adpcmWave->book->order * alBank->percussion->sounds[y]->wav.adpcmWave->book->npredictors * 8); z++)
						{
							temporaryCtlBuffer[outputCtlCounter++] = ((alBank->percussion->sounds[y]->wav.adpcmWave->book->predictors[z] >> 8) & 0xFF);
							temporaryCtlBuffer[outputCtlCounter++] = ((alBank->percussion->sounds[y]->wav.adpcmWave->book->predictors[z]) & 0xFF);
						}

						
						// game does this not sure why
						/*int pad = 8;
						for (int z = 0; z < pad; z++)
						{
							temporaryCtlBuffer[outputCtlCounter++] = 0;
						}*/
					}
					else
					{
						WriteLongToBuffer(temporaryCtlBuffer, bookWriteSpot, percussionbookOffsetsWav[same]);
					}
				}
				else if (alBank->percussion->sounds[y]->wav.type == AL_RAW16_WAVE)
				{

					if (alBank->percussion->sounds[y]->wav.rawWave->loop != NULL)
					{
						int same = -1;

						int loopEnd = y;
						
						for (int w = 0; w < loopEnd; w++)
						{
							if ((alBank->percussion->sounds[w]->wav.rawWave != NULL) && (alBank->percussion->sounds[w]->wav.rawWave->loop != NULL))
							{
								if ((alBank->percussion->sounds[y]->wav.rawWave->loop->start == alBank->percussion->sounds[w]->wav.rawWave->loop->start) 
									&& (alBank->percussion->sounds[y]->wav.rawWave->loop->end == alBank->percussion->sounds[w]->wav.rawWave->loop->end) 
									&& (alBank->percussion->sounds[y]->wav.rawWave->loop->count == alBank->percussion->sounds[w]->wav.rawWave->loop->count) 
									)
								{
									percussionrawLoopOffsetsWav[y] = percussionrawLoopOffsetsWav[w];
									same = w;
									break;
								}
							}
						}

						if (same == -1)
						{
							unsigned long loopWriteSpot = outputCtlCounter;

							outputCtlCounter += 4;

							if ((outputCtlCounter % 8) != 0)
							{
								int pad = 8 - (outputCtlCounter % 8);
								for (int z = 0; z < pad; z++)
								{
									temporaryCtlBuffer[outputCtlCounter++] = 0;
								}
							}

							percussionrawLoopOffsetsWav[y] = (outputCtlCounter);
							WriteLongToBuffer(temporaryCtlBuffer, loopWriteSpot, outputCtlCounter);

							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->percussion->sounds[y]->wav.rawWave->loop->start);
							outputCtlCounter += 4;
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->percussion->sounds[y]->wav.rawWave->loop->end);
							outputCtlCounter += 4;
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->percussion->sounds[y]->wav.rawWave->loop->count);
							outputCtlCounter += 4;
						}
						else
						{
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, percussionrawLoopOffsetsWav[same]);
							outputCtlCounter += 4;
						}
					}
					else
					{
						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, 0);
						outputCtlCounter += 4;
					}

					if ((outputCtlCounter % 8) != 0)
					{
						int pad = 8 - (outputCtlCounter % 8);
						for (int z = 0; z < pad; z++)
						{
							temporaryCtlBuffer[outputCtlCounter++] = 0;
						}
					}
				}
			}
		}

		if ((outputCtlCounter % 8) != 0)
		{
			int pad = 8 - (outputCtlCounter % 8);
			for (int z = 0; z < pad; z++)
			{
				temporaryCtlBuffer[outputCtlCounter++] = 0;
			}
		}
	}







	for (int x = 0; x < alBank->count; x++)
	{
		unsigned long wavStart = outputCtlCounter;

		for (int y = 0; y < alBank->inst[x]->soundCount; y++)
		{
			instrumentSoundStartLookup[x][y] = outputCtlCounter;

			offsetsWav[x][y] = outputCtlCounter + 0x10;

			bool entireSoundMatch = false;

			int entireMatchBank = -1;
			int entireMatch = -1;
			for (int r = 0; r < (x + 1); r++)
			{
				int loopEnd = y;
				if (r != x)
				{
					loopEnd = alBank->inst[r]->soundCount;
				}

				for (int w = 0; w < loopEnd; w++)
				{
					if (
						(alBank->inst[x]->sounds[y]->wav.base == alBank->inst[r]->sounds[w]->wav.base)
						&& (alBank->inst[x]->sounds[y]->wav.len == alBank->inst[r]->sounds[w]->wav.len)
						&& (alBank->inst[x]->sounds[y]->wav.flags == alBank->inst[r]->sounds[w]->wav.flags)
						&& (alBank->inst[x]->sounds[y]->wav.type == alBank->inst[r]->sounds[w]->wav.type)
						)
					{
						if (alBank->inst[x]->sounds[y]->wav.type == 0)
						{
							if (((alBank->inst[x]->sounds[y]->wav.adpcmWave->loop == NULL) && (alBank->inst[r]->sounds[w]->wav.adpcmWave->loop != NULL))
								|| ((alBank->inst[x]->sounds[y]->wav.adpcmWave->loop != NULL) && (alBank->inst[r]->sounds[w]->wav.adpcmWave->loop == NULL)))
							{
								continue;
							}

							bool sameLoop = false;
							if ((alBank->inst[x]->sounds[y]->wav.adpcmWave->loop == NULL) && (alBank->inst[r]->sounds[w]->wav.adpcmWave->loop == NULL))
							{
								sameLoop = true;
							}
							else
							{
								if (
									(alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start == alBank->inst[r]->sounds[w]->wav.adpcmWave->loop->start)
									&& (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end == alBank->inst[r]->sounds[w]->wav.adpcmWave->loop->end)
									&& (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count == alBank->inst[r]->sounds[w]->wav.adpcmWave->loop->count))
								{
									bool abort = false;
									for (int z = 0; z < 0x10; z++)
									{
										if (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z] != alBank->inst[r]->sounds[w]->wav.adpcmWave->loop->state[z])
										{
											abort = true;
											break;
										}
									}

									if (abort)
										continue;
									else

										sameLoop = true;
								}
								else
								{
									continue;
								}
							}

							if (sameLoop)
							{
								if ((alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors == alBank->inst[r]->sounds[w]->wav.adpcmWave->book->npredictors)
									&& (alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order == alBank->inst[r]->sounds[w]->wav.adpcmWave->book->order))
								{
									bool abort = false;
									for (int z = 0; z < (alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * 8); z++)
									{
										if (alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] != alBank->inst[r]->sounds[w]->wav.adpcmWave->book->predictors[z])
										{
											abort = true;
											break;
										}
									}

									if (abort)
										continue;
									else
									{
										entireMatchBank = r;
										entireMatch = w;
										offsetsWav[x][y] = offsetsWav[entireMatchBank][entireMatch];
										bookOffsetsWav[x][y] = bookOffsetsWav[entireMatchBank][entireMatch];
										tblOffsets[x][y] = tblOffsets[entireMatchBank][entireMatch];


										if (
											(alBank->inst[x]->sounds[y]->env.attackTime == alBank->inst[entireMatchBank]->sounds[entireMatch]->env.attackTime)
											&& (alBank->inst[x]->sounds[y]->env.attackVolume == alBank->inst[entireMatchBank]->sounds[entireMatch]->env.attackVolume)
											&& (alBank->inst[x]->sounds[y]->env.decayTime == alBank->inst[entireMatchBank]->sounds[entireMatch]->env.decayTime)
											&& (alBank->inst[x]->sounds[y]->env.decayVolume == alBank->inst[entireMatchBank]->sounds[entireMatch]->env.decayVolume)
											&& (alBank->inst[x]->sounds[y]->env.releaseTime == alBank->inst[entireMatchBank]->sounds[entireMatch]->env.releaseTime)
											&& (alBank->inst[x]->sounds[y]->samplePan == alBank->inst[entireMatchBank]->sounds[entireMatch]->samplePan)
											&& (alBank->inst[x]->sounds[y]->sampleVolume == alBank->inst[entireMatchBank]->sounds[entireMatch]->sampleVolume)
											&& (alBank->inst[x]->sounds[y]->flags == alBank->inst[entireMatchBank]->sounds[entireMatch]->flags)
											&& (alBank->inst[x]->sounds[y]->key.detune == alBank->inst[entireMatchBank]->sounds[entireMatch]->key.detune)
											&& (alBank->inst[x]->sounds[y]->key.keybase == alBank->inst[entireMatchBank]->sounds[entireMatch]->key.keybase)
											&& (alBank->inst[x]->sounds[y]->key.keymax == alBank->inst[entireMatchBank]->sounds[entireMatch]->key.keymax)
											&& (alBank->inst[x]->sounds[y]->key.keymin == alBank->inst[entireMatchBank]->sounds[entireMatch]->key.keymin)
											&& (alBank->inst[x]->sounds[y]->key.velocitymax == alBank->inst[entireMatchBank]->sounds[entireMatch]->key.velocitymax)
											&& (alBank->inst[x]->sounds[y]->key.velocitymin == alBank->inst[entireMatchBank]->sounds[entireMatch]->key.velocitymin)
											)
										{
											instrumentSoundStartLookup[x][y] = instrumentSoundStartLookup[entireMatchBank][entireMatch];
											entireSoundMatch = true;
											break;
										}
										else
										{
											continue;
										}
										
									}
								}
								else
								{
									continue;
								}
							}
						}
						else
						{
							if (((alBank->inst[x]->sounds[y]->wav.rawWave->loop == NULL) && (alBank->inst[r]->sounds[w]->wav.rawWave->loop != NULL))
								|| ((alBank->inst[x]->sounds[y]->wav.rawWave->loop != NULL) && (alBank->inst[r]->sounds[w]->wav.rawWave->loop == NULL)))
							{
								continue;
							}

							bool sameLoop = false;
							if ((alBank->inst[x]->sounds[y]->wav.rawWave->loop == NULL) && (alBank->inst[r]->sounds[w]->wav.rawWave->loop == NULL))
							{
								sameLoop = true;
							}
							else
							{
								if (
									(alBank->inst[x]->sounds[y]->wav.rawWave->loop->start == alBank->inst[r]->sounds[w]->wav.rawWave->loop->start)
									&& (alBank->inst[x]->sounds[y]->wav.rawWave->loop->end == alBank->inst[r]->sounds[w]->wav.rawWave->loop->end)
									&& (alBank->inst[x]->sounds[y]->wav.rawWave->loop->count == alBank->inst[r]->sounds[w]->wav.rawWave->loop->count))
								{
									entireMatchBank = r;
									entireMatch = w;
									offsetsWav[x][y] = offsetsWav[entireMatchBank][entireMatch];
									bookOffsetsWav[x][y] = bookOffsetsWav[entireMatchBank][entireMatch];
									tblOffsets[x][y] = tblOffsets[entireMatchBank][entireMatch];
									
									if (
											(alBank->inst[x]->sounds[y]->env.attackTime == alBank->inst[entireMatchBank]->sounds[entireMatch]->env.attackTime)
											&& (alBank->inst[x]->sounds[y]->env.attackVolume == alBank->inst[entireMatchBank]->sounds[entireMatch]->env.attackVolume)
											&& (alBank->inst[x]->sounds[y]->env.decayTime == alBank->inst[entireMatchBank]->sounds[entireMatch]->env.decayTime)
											&& (alBank->inst[x]->sounds[y]->env.decayVolume == alBank->inst[entireMatchBank]->sounds[entireMatch]->env.decayVolume)
											&& (alBank->inst[x]->sounds[y]->env.releaseTime == alBank->inst[entireMatchBank]->sounds[entireMatch]->env.releaseTime)
											&& (alBank->inst[x]->sounds[y]->samplePan == alBank->inst[entireMatchBank]->sounds[entireMatch]->samplePan)
											&& (alBank->inst[x]->sounds[y]->sampleVolume == alBank->inst[entireMatchBank]->sounds[entireMatch]->sampleVolume)
											&& (alBank->inst[x]->sounds[y]->flags == alBank->inst[entireMatchBank]->sounds[entireMatch]->flags)
											&& (alBank->inst[x]->sounds[y]->key.detune == alBank->inst[entireMatchBank]->sounds[entireMatch]->key.detune)
											&& (alBank->inst[x]->sounds[y]->key.keybase == alBank->inst[entireMatchBank]->sounds[entireMatch]->key.keybase)
											&& (alBank->inst[x]->sounds[y]->key.keymax == alBank->inst[entireMatchBank]->sounds[entireMatch]->key.keymax)
											&& (alBank->inst[x]->sounds[y]->key.keymin == alBank->inst[entireMatchBank]->sounds[entireMatch]->key.keymin)
											&& (alBank->inst[x]->sounds[y]->key.velocitymax == alBank->inst[entireMatchBank]->sounds[entireMatch]->key.velocitymax)
											&& (alBank->inst[x]->sounds[y]->key.velocitymin == alBank->inst[entireMatchBank]->sounds[entireMatch]->key.velocitymin)
											)
										{
											instrumentSoundStartLookup[x][y] = instrumentSoundStartLookup[entireMatchBank][entireMatch];
											entireSoundMatch = true;
											break;
										}
										else
										{
											continue;
										}
								}
								else
								{
									continue;
								}
							}
						}
					}
				}
			}

			

			if (!entireSoundMatch)
			{
				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, offsetsEnv[x][y]);
				outputCtlCounter += 4;
				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, offsetsKey[x][y]);
				outputCtlCounter += 4;

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, offsetsWav[x][y]);
				outputCtlCounter += 4;

				temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[x]->sounds[y]->samplePan;
				temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[x]->sounds[y]->sampleVolume;
				WriteShortToBuffer(temporaryCtlBuffer, outputCtlCounter, 0);
				outputCtlCounter += 2;
			}

			if (entireMatch == -1)
			{
			
				tblOffsets[x][y] = outputTblCounter;

				int foundSameTbl = false;

				for (int r = 0; r < (x + 1); r++)
				{
					int loopEnd = y;
					if (r != x)
					{
						loopEnd = alBank->inst[r]->soundCount;
					}
					for (int z = 0; z < loopEnd; z++)
					{
						if (
							(alBank->inst[x]->sounds[y]->wav.base == alBank->inst[r]->sounds[z]->wav.base)
							&& (alBank->inst[x]->sounds[y]->wav.len == alBank->inst[r]->sounds[z]->wav.len)
							)
						{
							bool mismatchValues = false;
							for (int rr = 0; rr < alBank->inst[x]->sounds[y]->wav.len; rr++)
							{
								if (alBank->inst[x]->sounds[y]->wav.wavData[rr] != alBank->inst[r]->sounds[z]->wav.wavData[rr])
								{
									mismatchValues = true;
									break;
								}
							}
							if (!mismatchValues)
							{
								foundSameTbl = true;
								tblOffsets[x][y] = tblOffsets[r][z];
								break;
							}
							else
							{
								continue;
							}
						}
					}
				}

				// update base
				//alBank->inst[x]->sounds[y]->wav.base = tblOffsets[x][y];

				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, tblOffsets[x][y]);
				outputCtlCounter += 4;
				WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->wav.len);
				outputCtlCounter += 4;

				if (!foundSameTbl)
				{
					for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.len; z++)
					{
						temporaryTblBuffer[outputTblCounter + z] = alBank->inst[x]->sounds[y]->wav.wavData[z];
					}
					outputTblCounter += alBank->inst[x]->sounds[y]->wav.len;

					if ((outputTblCounter % 8) != 0)
					{
						int pad = 8 - (outputTblCounter % 8);
						for (int z = 0; z < pad; z++)
						{
							temporaryTblBuffer[outputTblCounter++] = 0;
						}
					}
				}

				temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[x]->sounds[y]->wav.type;
				temporaryCtlBuffer[outputCtlCounter++] = 0; // offset type
				temporaryCtlBuffer[outputCtlCounter++] = 0; // pad
				temporaryCtlBuffer[outputCtlCounter++] = 0; // pad

				if (alBank->inst[x]->sounds[y]->wav.type == AL_ADPCM_WAVE)
				{
					int sameLoop = -1;
					int sameLoopBank = -1;


					if (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop != NULL)
					{
						for (int r = 0; r < (x + 1); r++)
						{
							if (sameLoop != -1)
								break;

							int loopEnd = y;
							if (r != x)
							{
								loopEnd = alBank->inst[r]->soundCount;
							}
							for (int w = 0; w < loopEnd; w++)
							{
								if ((alBank->inst[r]->sounds[w]->wav.adpcmWave != NULL) && (alBank->inst[r]->sounds[w]->wav.adpcmWave->loop != NULL))
								{
									if ((alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start == alBank->inst[r]->sounds[w]->wav.adpcmWave->loop->start) 
										&& (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end == alBank->inst[r]->sounds[w]->wav.adpcmWave->loop->end)
										&& (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count == alBank->inst[r]->sounds[w]->wav.adpcmWave->loop->count))
									{
										bool goOn = false;
										for (int ww = 0; ww < 0x10; ww++)
										{
											if (alBank->inst[r]->sounds[w]->wav.adpcmWave->loop->state[ww] != alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[ww])
											{
												goOn = true;
												break;
											}
										}

										if (goOn)
											continue;

										adpcmRawLoopOffsetsWav[x][y] = adpcmRawLoopOffsetsWav[r][w];
										sameLoopBank = r;
										sameLoop = w;
										break;
									}
								}
							}
						}
					}

					unsigned long loopWriteSpot = outputCtlCounter;
					unsigned long bookWriteSpot = outputCtlCounter + 4;
					 
					int same = -1;
					int sameBank = -1;

					for (int r = 0; r < (x + 1); r++)
					{
						if (same != -1)
							break;

						int loopEnd = y;
						if (r != x)
						{
							loopEnd = alBank->inst[r]->soundCount;
						}
						for (int w = 0; w < loopEnd; w++)
						{
							if (alBank->inst[r]->sounds[w]->wav.adpcmWave != NULL)
							{
								if ((alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order == alBank->inst[r]->sounds[w]->wav.adpcmWave->book->order) 
									&& (alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors == alBank->inst[r]->sounds[w]->wav.adpcmWave->book->npredictors))
								{
									bool goOn = false;
									for (int ww = 0; ww < (alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8); ww++)
									{
										if (alBank->inst[r]->sounds[w]->wav.adpcmWave->book->predictors[ww] != alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[ww])
										{
											goOn = true;
											break;
										}
									}

									if (goOn)
										continue;

									sameBank = r;
									same = w;
									break;
								}
							}
						}
					}

					// write later loop/predictor offsets
					outputCtlCounter += 8;


					if ((outputCtlCounter % 8) != 0)
					{
						int pad = 8 - (outputCtlCounter % 8);
						for (int z = 0; z < pad; z++)
						{
							temporaryCtlBuffer[outputCtlCounter++] = 0;
						}
					}

					if (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop != NULL)
					{
						if (sameLoop == -1)
						{
							bool foundSameInPercussion = false;
							if (alBank->percussion != NULL)
							{
								for (int w = 0; w < alBank->percussion->soundCount; w++)
								{
									if (alBank->percussion->sounds[w]->wav.adpcmWave->loop != NULL)
									{
										if ((alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start == alBank->percussion->sounds[w]->wav.adpcmWave->loop->start) 
												&& (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end == alBank->percussion->sounds[w]->wav.adpcmWave->loop->end)
												&& (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count == alBank->percussion->sounds[w]->wav.adpcmWave->loop->count))
										{
											bool goOn = false;
											for (int ww = 0; ww < 0x10; ww++)
											{
												if (alBank->percussion->sounds[w]->wav.adpcmWave->loop->state[ww] != alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[ww])
												{
													goOn = true;
													break;
												}
											}

											if (goOn)
												continue;

											adpcmRawLoopOffsetsWav[x][y] = percussionadpcmRawLoopOffsetsWav[w];

											foundSameInPercussion = true;
											break;
										}
									}
								}
							}
							
							if (!foundSameInPercussion)
							{
								adpcmRawLoopOffsetsWav[x][y] = outputCtlCounter;
								WriteLongToBuffer(temporaryCtlBuffer, loopWriteSpot, outputCtlCounter);

								WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start);
								outputCtlCounter += 4;
								WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end);
								outputCtlCounter += 4;
								WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count);
								outputCtlCounter += 4;
								for (int z = 0; z < 0x10; z++)
								{
									temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z] >> 8) & 0xFF);
									temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z]) & 0xFF);
								}
							}
							else
							{
								WriteLongToBuffer(temporaryCtlBuffer, loopWriteSpot, adpcmRawLoopOffsetsWav[x][y]);
							}
						}
						else
						{
							WriteLongToBuffer(temporaryCtlBuffer, loopWriteSpot, adpcmRawLoopOffsetsWav[sameLoopBank][sameLoop]);
						}
					}
					else
					{
						// null loop
						WriteLongToBuffer(temporaryCtlBuffer, loopWriteSpot, 0x0);
					}

					if ((outputCtlCounter % 8) != 0)
					{
						int pad = 8 - (outputCtlCounter % 8);
						for (int z = 0; z < pad; z++)
						{
							temporaryCtlBuffer[outputCtlCounter++] = 0;
						}
					}

					if (same == -1)
					{
						bool foundSameInPercussion = false;

						if (alBank->percussion != NULL)
						{
							for (int w = 0; w < alBank->percussion->soundCount; w++)
							{
								if (alBank->percussion->sounds[w]->wav.adpcmWave != NULL)
								{
									if ((alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order == alBank->percussion->sounds[w]->wav.adpcmWave->book->order) 
										&& (alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors == alBank->percussion->sounds[w]->wav.adpcmWave->book->npredictors))
									{
										bool goOn = false;
										for (int ww = 0; ww < (alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8); ww++)
										{
											if (alBank->percussion->sounds[w]->wav.adpcmWave->book->predictors[ww] != alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[ww])
											{
												goOn = true;
												break;
											}
										}

										if (goOn)
											continue;

										bookOffsetsWav[x][y] = percussionbookOffsetsWav[w];
										foundSameInPercussion = true;
										break;
									}
								}
							}
						}

						if (!foundSameInPercussion)
						{
							bookOffsetsWav[x][y] = outputCtlCounter;
							WriteLongToBuffer(temporaryCtlBuffer, bookWriteSpot, outputCtlCounter);

							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order);
							outputCtlCounter += 4;
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors);
							outputCtlCounter += 4;

							for (int z = 0; z < (alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8); z++)
							{
								temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] >> 8) & 0xFF);
								temporaryCtlBuffer[outputCtlCounter++] = ((alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z]) & 0xFF);
							}
						}
						else
						{
							WriteLongToBuffer(temporaryCtlBuffer, bookWriteSpot, bookOffsetsWav[x][y]);
						}

						
						// game does this not sure why
						/*int pad = 8;
						for (int z = 0; z < pad; z++)
						{
							temporaryCtlBuffer[outputCtlCounter++] = 0;
						}*/
					}
					else
					{
						WriteLongToBuffer(temporaryCtlBuffer, bookWriteSpot, bookOffsetsWav[sameBank][same]);
					}
				}
				else if (alBank->inst[x]->sounds[y]->wav.type == AL_RAW16_WAVE)
				{

					if (alBank->inst[x]->sounds[y]->wav.rawWave->loop != NULL)
					{
						int sameBank = -1;
						int same = -1;

						for (int r = 0; r < (x + 1); r++)
						{
							if (same != -1)
								break;

							int loopEnd = y;
							if (r != x)
							{
								loopEnd = alBank->inst[r]->soundCount;
							}
							for (int w = 0; w < loopEnd; w++)
							{
								if ((alBank->inst[r]->sounds[w]->wav.rawWave != NULL) && (alBank->inst[r]->sounds[w]->wav.rawWave->loop != NULL))
								{
									if ((alBank->inst[x]->sounds[y]->wav.rawWave->loop->start == alBank->inst[r]->sounds[w]->wav.rawWave->loop->start) 
										&& (alBank->inst[x]->sounds[y]->wav.rawWave->loop->end == alBank->inst[r]->sounds[w]->wav.rawWave->loop->end) 
										&& (alBank->inst[x]->sounds[y]->wav.rawWave->loop->count == alBank->inst[r]->sounds[w]->wav.rawWave->loop->count) 
										)
									{
										sameBank = r;
										rawLoopOffsetsWav[x][y] = rawLoopOffsetsWav[r][w];
										same = w;
										break;
									}
								}
							}
						}

						if (same == -1)
						{
							unsigned long loopWriteSpot = outputCtlCounter;

							outputCtlCounter += 4;

							if ((outputCtlCounter % 8) != 0)
							{
								int pad = 8 - (outputCtlCounter % 8);
								for (int z = 0; z < pad; z++)
								{
									temporaryCtlBuffer[outputCtlCounter++] = 0;
								}
							}

							rawLoopOffsetsWav[x][y] = (outputCtlCounter);
							WriteLongToBuffer(temporaryCtlBuffer, loopWriteSpot, outputCtlCounter);

							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->wav.rawWave->loop->start);
							outputCtlCounter += 4;
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->wav.rawWave->loop->end);
							outputCtlCounter += 4;
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[x]->sounds[y]->wav.rawWave->loop->count);
							outputCtlCounter += 4;
						}
						else
						{
							WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, rawLoopOffsetsWav[sameBank][same]);
							outputCtlCounter += 4;
						}
					}
					else
					{
						WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, 0);
						outputCtlCounter += 4;
					}

					if ((outputCtlCounter % 8) != 0)
					{
						int pad = 8 - (outputCtlCounter % 8);
						for (int z = 0; z < pad; z++)
						{
							temporaryCtlBuffer[outputCtlCounter++] = 0;
						}
					}
				}
			}
		}

		if ((outputCtlCounter % 8) != 0)
		{
			int pad = 8 - (outputCtlCounter % 8);
			for (int z = 0; z < pad; z++)
			{
				temporaryCtlBuffer[outputCtlCounter++] = 0;
			}
		}
	}

	unsigned long startALSound = outputCtlCounter;

	if (alBank->percussion != NULL)
	{
		percussionALLookup = outputCtlCounter;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->volume;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->pan;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->priority;
		temporaryCtlBuffer[outputCtlCounter++] = 0; //offset type
		temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->tremType;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->tremRate;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->tremDepth;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->tremDelay;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->vibType;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->vibRate;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->vibDepth;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->percussion->vibDelay;
		WriteShortToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->percussion->bendRange);
		outputCtlCounter += 2;
		WriteShortToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->percussion->soundCount);
		outputCtlCounter += 2;
		
		for (int z = 0; z < alBank->percussion->soundCount; z++)
		{
			WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, (percussioninstrumentSoundStartLookup[z]));
			outputCtlCounter += 4;
		}

		if ((outputCtlCounter % 8) != 0)
		{
			int pad = 8 - (outputCtlCounter % 8);
			for (int z = 0; z < pad; z++)
			{
				temporaryCtlBuffer[outputCtlCounter++] = 0;
			}
		}
	}

	for (int y = 0; y < alBank->count; y++)
	{
		instrumentALLookup[y] = outputCtlCounter;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[y]->volume;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[y]->pan;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[y]->priority;
		temporaryCtlBuffer[outputCtlCounter++] = 0; //offset type
		temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[y]->tremType;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[y]->tremRate;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[y]->tremDepth;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[y]->tremDelay;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[y]->vibType;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[y]->vibRate;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[y]->vibDepth;
		temporaryCtlBuffer[outputCtlCounter++] = alBank->inst[y]->vibDelay;
		WriteShortToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->bendRange);
		outputCtlCounter += 2;
		WriteShortToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->inst[y]->soundCount);
		outputCtlCounter += 2;
		
		for (int z = 0; z < alBank->inst[y]->soundCount; z++)
		{
			WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, (instrumentSoundStartLookup[y][z]));
			outputCtlCounter += 4;
		}

		if ((outputCtlCounter % 8) != 0)
		{
			int pad = 8 - (outputCtlCounter % 8);
			for (int z = 0; z < pad; z++)
			{
				temporaryCtlBuffer[outputCtlCounter++] = 0;
			}
		}
	}

	if ((outputCtlCounter % 8) != 0)
	{
		int pad = 8 - (outputCtlCounter % 8);
		for (int z = 0; z < pad; z++)
		{
			temporaryCtlBuffer[outputCtlCounter++] = 0;
		}
	}

	unsigned long startBank = outputCtlCounter;
	WriteLongToBuffer(temporaryCtlBuffer, 0x4, startBank);

	WriteShortToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->count);
	outputCtlCounter += 2;
	WriteShortToBuffer(temporaryCtlBuffer, outputCtlCounter, 0); // offset type
	outputCtlCounter += 2;
	WriteShortToBuffer(temporaryCtlBuffer, outputCtlCounter, alBank->pad);
	outputCtlCounter += 2;
	WriteShortToBuffer(temporaryCtlBuffer, outputCtlCounter, (alBank->samplerate));
	outputCtlCounter += 2;

	if (alBank->percussion != NULL)
	{
		WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, percussionALLookup);
		outputCtlCounter += 4;
	}
	else
	{
		WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, 0x00000000);
		outputCtlCounter += 4;
	}

	for (int y = 0; y < alBank->count; y++)
	{
		WriteLongToBuffer(temporaryCtlBuffer, outputCtlCounter, instrumentALLookup[y]);
		outputCtlCounter += 4;
	}
	outputCtlCounter += 4;

	if ((outputCtlCounter % 0x10) != 0)
	{
		int pad = 0x10 - (outputCtlCounter % 0x10);
		for (int z = 0; z < pad; z++)
		{
			temporaryCtlBuffer[outputCtlCounter++] = 0;
		}
	}

	for (int x = 0; x < alBank->count; x++)
	{
		delete [] instrumentSoundStartLookup[x];
		delete [] offsetsEnv[x];;
		delete [] offsetsKey[x];;
		delete [] offsetsWav[x];;
		delete [] bookOffsetsWav[x];;
		delete [] adpcmRawLoopOffsetsWav[x];;
		delete [] rawLoopOffsetsWav[x];;
		delete [] tblOffsets[x];;
	}

	delete [] instrumentSoundStartLookup;
	delete [] instrumentALLookup;
	delete [] offsetsEnv;
	delete [] offsetsKey;
	delete [] offsetsWav;
	delete [] bookOffsetsWav;
	delete [] adpcmRawLoopOffsetsWav;
	delete [] rawLoopOffsetsWav;
	delete [] tblOffsets;

	if (alBank->percussion != NULL)
	{
		delete [] percussioninstrumentSoundStartLookup;
		delete [] percussionoffsetsEnv;
		delete [] percussionoffsetsKey;
		delete [] percussionoffsetsWav;
		delete [] percussionbookOffsetsWav;
		delete [] percussionadpcmRawLoopOffsetsWav;
		delete [] percussionrawLoopOffsetsWav;
		delete [] percussiontblOffsets;
	}
	
	ctl = temporaryCtlBuffer;
	tbl = temporaryTblBuffer;

	ctlSize = outputCtlCounter;
	tblSize = outputTblCounter;
}

bool CN64AIFCAudio::InjectCtlTblIntoROMArrayInPlace(unsigned char* ROM, unsigned char* ctl, int ctlSize, unsigned char* tbl, int tblSize, unsigned long ctlOffset, unsigned long tblOffset, unsigned long maxCtl, unsigned long maxTbl)
{
	if (ctlSize > maxCtl)
	{
		MessageBox(NULL, "Error ctl too big", "Error", NULL);
		return false;
	}
	if (tblSize > maxTbl)
	{
		MessageBox(NULL, "Error tbl too big", "Error", NULL);
		return false;
	}
	for (int x = ctlOffset; x < (ctlOffset + ctlSize); x++)
	{
		ROM[x] = ctl[x - ctlOffset];
	}
	for (int x = tblOffset; x < (tblOffset + tblSize); x++)
	{
		ROM[x] = tbl[x - tblOffset];
	}
	return true;
}

void CN64AIFCAudio::DisposeALBank(ALBank*& alBank)
{
	if (alBank != NULL)
	{
		if (alBank->eadPercussion != NULL)
		{
			for (int y = 0; y < alBank->countEADPercussion; y++)
			{
				if (alBank->eadPercussion[y].wav.type == AL_ADPCM_WAVE)
				{
					if (alBank->eadPercussion[y].wav.adpcmWave != NULL)
					{
						if (alBank->eadPercussion[y].wav.adpcmWave->loop != NULL)
						{
							delete alBank->eadPercussion[y].wav.adpcmWave->loop;
						}
						if (alBank->eadPercussion[y].wav.adpcmWave->book != NULL)
						{
							delete [] alBank->eadPercussion[y].wav.adpcmWave->book->predictors;
							delete alBank->eadPercussion[y].wav.adpcmWave->book;
						}
						delete alBank->eadPercussion[y].wav.adpcmWave;
					}
				}
				else if (alBank->eadPercussion[y].wav.type == AL_RAW16_WAVE)
				{
					if (alBank->eadPercussion[y].wav.rawWave != NULL)
					{
						if (alBank->eadPercussion[y].wav.rawWave->loop != NULL)
						{
							delete alBank->eadPercussion[y].wav.rawWave->loop;
						}
						delete alBank->eadPercussion[y].wav.rawWave;
					}
				}
				else if (alBank->eadPercussion[y].wav.type == AL_MUSYX_WAVE)
				{
					if (alBank->eadPercussion[y].wav.adpcmWave != NULL)
					{
						if (alBank->eadPercussion[y].wav.adpcmWave->loop != NULL)
						{
							delete alBank->eadPercussion[y].wav.adpcmWave->loop;
						}
						delete alBank->eadPercussion[y].wav.adpcmWave;
					}
				}

				if (alBank->eadPercussion[y].wav.wavData != NULL)
					delete [] alBank->eadPercussion[y].wav.wavData;
			}

			delete [] alBank->eadPercussion;
		}

		if (alBank->alSfx != NULL)
		{
			for (int x = 0; x < alBank->countSfx; x++)
			{
				if (alBank->alSfx[x] != NULL)
				{
					if (alBank->alSfx[x]->type == AL_ADPCM_WAVE)
					{
						if (alBank->alSfx[x]->adpcmWave != NULL)
						{
							if (alBank->alSfx[x]->adpcmWave->loop != NULL)
							{
								delete alBank->alSfx[x]->adpcmWave->loop;
							}
							if (alBank->alSfx[x]->adpcmWave->book != NULL)
							{
								delete [] alBank->alSfx[x]->adpcmWave->book->predictors;
								delete alBank->alSfx[x]->adpcmWave->book;
							}
							delete alBank->alSfx[x]->adpcmWave;
						}
					}
					else if (alBank->alSfx[x]->type == AL_RAW16_WAVE)
					{
						if (alBank->alSfx[x]->rawWave != NULL)
						{
							if (alBank->alSfx[x]->rawWave->loop != NULL)
							{
								delete alBank->alSfx[x]->rawWave->loop;
							}
							delete alBank->alSfx[x]->rawWave;
						}
					}
					else if (alBank->alSfx[x]->type == AL_MUSYX_WAVE)
					{
						if (alBank->alSfx[x]->adpcmWave != NULL)
						{
							if (alBank->alSfx[x]->adpcmWave->loop != NULL)
							{
								delete alBank->alSfx[x]->adpcmWave->loop;
							}
							if (alBank->alSfx[x]->adpcmWave->book != NULL)
							{
								delete [] alBank->alSfx[x]->adpcmWave->book->predictors;
								delete alBank->alSfx[x]->adpcmWave->book;
							}
							delete alBank->alSfx[x]->adpcmWave;
						}
					}

					if (alBank->alSfx[x]->wavData != NULL)
						delete [] alBank->alSfx[x]->wavData;

					delete alBank->alSfx[x];
				}
			}

			delete [] alBank->alSfx;
		}

		if (alBank->percussion != NULL)
		{
			if (alBank->percussion->sounds != NULL)
			{
				for (int y = 0; y < alBank->percussion->soundCount; y++)
				{
					if (alBank->percussion->sounds[y] != NULL)
					{
						if (alBank->percussion->sounds[y]->wav.type == AL_ADPCM_WAVE)
						{
							if (alBank->percussion->sounds[y]->wav.adpcmWave != NULL)
							{
								if (alBank->percussion->sounds[y]->wav.adpcmWave->loop != NULL)
								{
									delete alBank->percussion->sounds[y]->wav.adpcmWave->loop;
								}
								if (alBank->percussion->sounds[y]->wav.adpcmWave->book != NULL)
								{
									delete [] alBank->percussion->sounds[y]->wav.adpcmWave->book->predictors;
									delete alBank->percussion->sounds[y]->wav.adpcmWave->book;
								}
								delete alBank->percussion->sounds[y]->wav.adpcmWave;
							}
						}
						else if (alBank->percussion->sounds[y]->wav.type == AL_RAW16_WAVE)
						{
							if (alBank->percussion->sounds[y]->wav.rawWave != NULL)
							{
								if (alBank->percussion->sounds[y]->wav.rawWave->loop != NULL)
								{
									delete alBank->percussion->sounds[y]->wav.rawWave->loop;
								}
								delete alBank->percussion->sounds[y]->wav.rawWave;
							}
						}
						else if (alBank->percussion->sounds[y]->wav.type == AL_MUSYX_WAVE)
						{
							if (alBank->percussion->sounds[y]->wav.adpcmWave != NULL)
							{
								if (alBank->percussion->sounds[y]->wav.adpcmWave->loop != NULL)
								{
									delete alBank->percussion->sounds[y]->wav.adpcmWave->loop;
								}
								if (alBank->percussion->sounds[y]->wav.adpcmWave->book != NULL)
								{
									delete [] alBank->percussion->sounds[y]->wav.adpcmWave->book->predictors;
									delete alBank->percussion->sounds[y]->wav.adpcmWave->book;
								}
								delete alBank->percussion->sounds[y]->wav.adpcmWave;
							}
						}

						if (alBank->percussion->sounds[y]->wav.wavData != NULL)
							delete [] alBank->percussion->sounds[y]->wav.wavData;




						if (alBank->percussion->sounds[y]->hasWavePrevious)
						{
							if (alBank->percussion->sounds[y]->wavPrevious.type == AL_ADPCM_WAVE)
							{
								if (alBank->percussion->sounds[y]->wavPrevious.adpcmWave != NULL)
								{
									if (alBank->percussion->sounds[y]->wavPrevious.adpcmWave->loop != NULL)
									{
										delete alBank->percussion->sounds[y]->wavPrevious.adpcmWave->loop;
									}
									delete [] alBank->percussion->sounds[y]->wavPrevious.adpcmWave->book->predictors;
									delete alBank->percussion->sounds[y]->wavPrevious.adpcmWave->book;
									delete alBank->percussion->sounds[y]->wavPrevious.adpcmWave;
								}
							}
							else if (alBank->percussion->sounds[y]->wavPrevious.type== AL_RAW16_WAVE)
							{
								if (alBank->percussion->sounds[y]->wavPrevious.rawWave != NULL)
								{
									if (alBank->percussion->sounds[y]->wavPrevious.rawWave->loop != NULL)
									{
										delete alBank->percussion->sounds[y]->wavPrevious.rawWave->loop;
									}
									delete alBank->percussion->sounds[y]->wavPrevious.rawWave;
								}
							}
							else if (alBank->percussion->sounds[y]->wavPrevious.type == AL_MUSYX_WAVE)
							{
								if (alBank->percussion->sounds[y]->wavPrevious.adpcmWave != NULL)
								{
									if (alBank->percussion->sounds[y]->wavPrevious.adpcmWave->loop != NULL)
									{
										delete alBank->percussion->sounds[y]->wavPrevious.adpcmWave->loop;
									}
									delete [] alBank->percussion->sounds[y]->wavPrevious.adpcmWave->book->predictors;
									delete alBank->percussion->sounds[y]->wavPrevious.adpcmWave->book;
									delete alBank->percussion->sounds[y]->wavPrevious.adpcmWave;
								}
							}

							if (alBank->percussion->sounds[y]->wavPrevious.wavData != NULL)
								delete [] alBank->percussion->sounds[y]->wavPrevious.wavData;
						}

						if (alBank->percussion->sounds[y]->hasWaveSecondary)
						{
							if (alBank->percussion->sounds[y]->wavSecondary.type == AL_ADPCM_WAVE)
							{
								if (alBank->percussion->sounds[y]->wavSecondary.adpcmWave != NULL)
								{
									if (alBank->percussion->sounds[y]->wavSecondary.adpcmWave->loop != NULL)
									{
										delete alBank->percussion->sounds[y]->wavSecondary.adpcmWave->loop;
									}
									delete [] alBank->percussion->sounds[y]->wavSecondary.adpcmWave->book->predictors;
									delete alBank->percussion->sounds[y]->wavSecondary.adpcmWave->book;
									delete alBank->percussion->sounds[y]->wavSecondary.adpcmWave;
								}
							}
							else if (alBank->percussion->sounds[y]->wavSecondary.type == AL_RAW16_WAVE)
							{
								if (alBank->percussion->sounds[y]->wavSecondary.rawWave != NULL)
								{
									if (alBank->percussion->sounds[y]->wavSecondary.rawWave->loop != NULL)
									{
										delete alBank->percussion->sounds[y]->wavSecondary.rawWave->loop;
									}
									delete alBank->percussion->sounds[y]->wavSecondary.rawWave;
								}
							}
							else if (alBank->percussion->sounds[y]->wavSecondary.type == AL_MUSYX_WAVE)
							{
								if (alBank->percussion->sounds[y]->wavSecondary.adpcmWave != NULL)
								{
									if (alBank->percussion->sounds[y]->wavSecondary.adpcmWave->loop != NULL)
									{
										delete alBank->percussion->sounds[y]->wavSecondary.adpcmWave->loop;
									}
									delete [] alBank->percussion->sounds[y]->wavSecondary.adpcmWave->book->predictors;
									delete alBank->percussion->sounds[y]->wavSecondary.adpcmWave->book;
									delete alBank->percussion->sounds[y]->wavSecondary.adpcmWave;
								}
							}

							if (alBank->percussion->sounds[y]->wavSecondary.wavData != NULL)
								delete [] alBank->percussion->sounds[y]->wavSecondary.wavData;
						}


						delete alBank->percussion->sounds[y];
					}
				}

				delete alBank->percussion->sounds;
			}

			delete alBank->percussion;
		}

		if (alBank->inst != NULL)
		{
			for (int x = 0; x < alBank->count; x++)
			{
				if (alBank->inst[x]->sounds != NULL)
				{
					for (int y = 0; y < alBank->inst[x]->soundCount; y++)
					{
						if (alBank->inst[x]->sounds[y] != NULL)
						{
							if (alBank->inst[x]->sounds[y]->wav.type == AL_ADPCM_WAVE)
							{
								if (alBank->inst[x]->sounds[y]->wav.adpcmWave != NULL)
								{
									if (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop != NULL)
									{
										delete alBank->inst[x]->sounds[y]->wav.adpcmWave->loop;
									}
									if (alBank->inst[x]->sounds[y]->wav.adpcmWave->book != NULL)
									{
										delete [] alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors;
										delete alBank->inst[x]->sounds[y]->wav.adpcmWave->book;
									}
									delete alBank->inst[x]->sounds[y]->wav.adpcmWave;
								}
							}
							else if (alBank->inst[x]->sounds[y]->wav.type == AL_RAW16_WAVE)
							{
								if (alBank->inst[x]->sounds[y]->wav.rawWave != NULL)
								{
									if (alBank->inst[x]->sounds[y]->wav.rawWave->loop != NULL)
									{
										delete alBank->inst[x]->sounds[y]->wav.rawWave->loop;
									}
									delete alBank->inst[x]->sounds[y]->wav.rawWave;
								}
							}
							else if (alBank->inst[x]->sounds[y]->wav.type == AL_MUSYX_WAVE)
							{
								if (alBank->inst[x]->sounds[y]->wav.adpcmWave != NULL)
								{
									if (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop != NULL)
									{
										delete alBank->inst[x]->sounds[y]->wav.adpcmWave->loop;
									}
									if (alBank->inst[x]->sounds[y]->wav.adpcmWave->book != NULL)
									{
										delete [] alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors;
										delete alBank->inst[x]->sounds[y]->wav.adpcmWave->book;
									}
									delete alBank->inst[x]->sounds[y]->wav.adpcmWave;
								}
							}

							if (alBank->inst[x]->sounds[y]->wav.wavData != NULL)
								delete [] alBank->inst[x]->sounds[y]->wav.wavData;




							if (alBank->inst[x]->sounds[y]->hasWavePrevious)
							{
								if (alBank->inst[x]->sounds[y]->wavPrevious.type == AL_ADPCM_WAVE)
								{
									if (alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave != NULL)
									{
										if (alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop != NULL)
										{
											delete alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop;
										}
										delete [] alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->predictors;
										delete alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book;
										delete alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave;
									}
								}
								else if (alBank->inst[x]->sounds[y]->wavPrevious.type== AL_RAW16_WAVE)
								{
									if (alBank->inst[x]->sounds[y]->wavPrevious.rawWave != NULL)
									{
										if (alBank->inst[x]->sounds[y]->wavPrevious.rawWave->loop != NULL)
										{
											delete alBank->inst[x]->sounds[y]->wavPrevious.rawWave->loop;
										}
										delete alBank->inst[x]->sounds[y]->wavPrevious.rawWave;
									}
								}
								else if (alBank->inst[x]->sounds[y]->wavPrevious.type == AL_MUSYX_WAVE)
								{
									if (alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave != NULL)
									{
										if (alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop != NULL)
										{
											delete alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop;
										}
										delete [] alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->predictors;
										delete alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book;
										delete alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave;
									}
								}

								if (alBank->inst[x]->sounds[y]->wavPrevious.wavData != NULL)
									delete [] alBank->inst[x]->sounds[y]->wavPrevious.wavData;
							}

							if (alBank->inst[x]->sounds[y]->hasWaveSecondary)
							{
								if (alBank->inst[x]->sounds[y]->wavSecondary.type == AL_ADPCM_WAVE)
								{
									if (alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave != NULL)
									{
										if (alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop != NULL)
										{
											delete alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop;
										}
										delete [] alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->predictors;
										delete alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book;
										delete alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave;
									}
								}
								else if (alBank->inst[x]->sounds[y]->wavSecondary.type == AL_RAW16_WAVE)
								{
									if (alBank->inst[x]->sounds[y]->wavSecondary.rawWave != NULL)
									{
										if (alBank->inst[x]->sounds[y]->wavSecondary.rawWave->loop != NULL)
										{
											delete alBank->inst[x]->sounds[y]->wavSecondary.rawWave->loop;
										}
										delete alBank->inst[x]->sounds[y]->wavSecondary.rawWave;
									}
								}
								else if (alBank->inst[x]->sounds[y]->wavSecondary.type == AL_MUSYX_WAVE)
								{
									if (alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave != NULL)
									{
										if (alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop != NULL)
										{
											delete alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop;
										}
										delete [] alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->predictors;
										delete alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book;
										delete alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave;
									}
								}

								if (alBank->inst[x]->sounds[y]->wavSecondary.wavData != NULL)
									delete [] alBank->inst[x]->sounds[y]->wavSecondary.wavData;
							}


							delete alBank->inst[x]->sounds[y];
						}
					}

					delete alBank->inst[x]->sounds;
				}

				delete alBank->inst[x];
			}

			delete alBank->inst;
		}

		delete alBank;
	}
}


ALBank* CN64AIFCAudio::ReadAudioTurok(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl, int bankTrueOffset, unsigned long mask, unsigned char* ROM, int bankNumber)
{
	ALBank* alBank = ReadAudio(ROM, &ROM[0], ctlSize, ctlOffset, tbl, bankTrueOffset, mask, bankNumber);
	if (alBank != NULL)
	{
		alBank->soundBankFormat = TUROKFORMAT;
	}
	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioN64PtrWavetableV1(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl)
{
	unsigned short numberBands = 1;
	unsigned long bankOffset = ctlOffset + 0x14;

	// header size 0x14
	ALBank* alBank = new ALBank();
	alBank->soundBankFormat = N64PTRWAVETABLETABLEV1;
	alBank->count = (unsigned short)CharArrayToLong(&ctl[ctlOffset+0x10]);
	alBank->flags = 0x0000;
	alBank->pad = 0x0;
	alBank->samplerate = 22050;
	alBank->percussion = 0x000;
	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = 0;
	
	alBank->inst = NULL;

	if ((alBank->flags == 0x0000) || (alBank->flags == 0x0100)) // offset
	{
		alBank->inst = new ALInst*[alBank->count];

		for (int x = 0; x < alBank->count; x++)
		{
			alBank->inst[x] = new ALInst();
			alBank->inst[x]->samplerate = 0;
			alBank->inst[x]->sounds = NULL;
		}

		for (int x = 0; x < alBank->count; x++)
		{
			unsigned long offsetInstrument = CharArrayToLong(&ctl[bankOffset + x*4]);
			if (offsetInstrument == 0x0000)
			{
				alBank->inst[x]->soundCount = 0;
				alBank->inst[x]->sounds = NULL;
				continue;
			}

			if (alBank->flags == 0x0100)
				offsetInstrument = offsetInstrument & 0xFFFFFF;
			else
				offsetInstrument = ctlOffset + offsetInstrument;

			if ((alBank->inst[x]->flags == 0x0) || (alBank->inst[x]->flags == 0x1))
			{	
				alBank->inst[x]->soundCount = 1;

				alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

				for (int y = 0; y < alBank->inst[x]->soundCount; y++)
				{
					alBank->inst[x]->sounds[y] = new ALSound();
					alBank->inst[x]->sounds[y]->wav.wavData = NULL;
				}

				for (int y = 0; y < alBank->inst[x]->soundCount; y++)
				{
					alBank->inst[x]->sounds[y]->flags = 0x0000;

					if ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1))
					{
						alBank->inst[x]->sounds[y]->wav.base = CharArrayToLong(&ctl[offsetInstrument + 0x0]);
						alBank->inst[x]->sounds[y]->wav.len = CharArrayToLong(&ctl[offsetInstrument + 0x4]);
						alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];

						for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
						{
							alBank->inst[x]->sounds[y]->wav.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wav.base + r];
						}
						

						alBank->inst[x]->sounds[y]->wav.type = AL_ADPCM_WAVE;
						alBank->inst[x]->sounds[y]->wav.flags = 0x0000;
						// MUST PAD to 4s

						if ((alBank->inst[x]->sounds[y]->wav.type == AL_ADPCM_WAVE) && ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1)))
						{
							alBank->inst[x]->sounds[y]->wav.adpcmWave = new ALADPCMWaveInfo();
							
							unsigned long predictorOffset = CharArrayToLong(&ctl[offsetInstrument + 0x10]);
							unsigned long loopOffset = CharArrayToLong(&ctl[offsetInstrument + 0xC]);

							if (loopOffset != 0)
							{
								if (alBank->inst[x]->sounds[y]->flags == 0x1)
									loopOffset = loopOffset & 0xFFFFFF;
								else
									loopOffset = ctlOffset + loopOffset;

								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = new ALADPCMloop();
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);
								for (int z = 0; z < 0x10; z++)
								{
									alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffset + 0xC + z * 2]);
								}
							}
							else
							{
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = NULL;
							}

						
							if (predictorOffset != 0x00000000)
							{
								if (alBank->inst[x]->sounds[y]->flags == 0x1)
									predictorOffset = predictorOffset & 0xFFFFFF;
								else
									predictorOffset = ctlOffset + predictorOffset;

								alBank->inst[x]->sounds[y]->wav.adpcmWave->book = new ALADPCMBook();
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffset + 0x0]);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffset + 0x4]);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8];

								for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8; z++)
								{
									alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + 0x8 + z * 2]);
								}
							}
							else
							{
								MessageBox(NULL, "Error", "Missing predictors in ALSound wav", NULL);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book = NULL;
							}
						}
						else
						{
							DisposeALBank(alBank);
							MessageBox(NULL, "Error", "Unsupported type in ALSound wav", NULL);
							return NULL;
						}
					}
					else
					{
						DisposeALBank(alBank);
						MessageBox(NULL, "Error", "Unsupported type in ALSound", NULL);
						return NULL;
					}
				}
			}
			else
			{
				DisposeALBank(alBank);
				MessageBox(NULL, "Error", "Unsupported inst type in ALInst", NULL);
				return NULL;
			}
		}
	}
	else
	{
		DisposeALBank(alBank);
		MessageBox(NULL, "Error", "Unsupported type in ALBank", NULL);
		return NULL;
	}

	return alBank;
}


ALBank* CN64AIFCAudio::ReadAudioH20Raw816(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl, int numberInstruments)
{
	ALBank* alBank = new ALBank();
	alBank->soundBankFormat = H20RAW816;
	alBank->count = 1;
	alBank->flags = 0;
	alBank->pad = 0;
	alBank->samplerate = 11025;
	alBank->percussion = 0;
	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = 0;

	alBank->inst = new ALInst*[alBank->count];

	for (int x = 0; x < alBank->count; x++)
	{
		alBank->inst[x] = new ALInst();
		alBank->inst[x]->samplerate = 0;
		alBank->inst[x]->sounds = NULL;
	}

	for (int x = 0; x < alBank->count; x++)
	{
		alBank->inst[x]->soundCount = 1;
		alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

		for (int y = 0; y < alBank->inst[x]->soundCount; y++)
		{
			alBank->inst[x]->sounds[y] = new ALSound();

			alBank->inst[x]->sounds[y]->hasWavePrevious = false;
			alBank->inst[x]->sounds[y]->hasWaveSecondary = false;
			alBank->inst[x]->sounds[y]->flags = 0;

			alBank->inst[x]->sounds[y]->wav.adpcmWave = NULL;
			alBank->inst[x]->sounds[y]->wav.rawWave = NULL;
			alBank->inst[x]->sounds[y]->wav.base = ctlOffset;

			CH20Decoder h20dec;
			unsigned char* tempBuffer = new unsigned char[0x100000];
			alBank->inst[x]->sounds[y]->wav.len = h20dec.decPolaris(&ctl[alBank->inst[x]->sounds[y]->wav.base], ctlSize, tempBuffer);

			alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];
			memcpy(alBank->inst[x]->sounds[y]->wav.wavData, tempBuffer, alBank->inst[x]->sounds[y]->wav.len);
			delete [] tempBuffer;
			
			if (numberInstruments == 0)
				alBank->inst[x]->sounds[y]->wav.type = AL_SIGNED_RAW8;
			else
				alBank->inst[x]->sounds[y]->wav.type = AL_SIGNED_RAW16;
		}
	}
	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioTetrisphereRaw816(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl, int numberInstruments)
{
	ALBank* alBank = new ALBank();
	alBank->soundBankFormat = TETRISPHERERAW816;
	alBank->count = 1;
	alBank->flags = 0;
	alBank->pad = 0;
	alBank->samplerate = 11025;
	alBank->percussion = 0;
	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = 0;

	alBank->inst = new ALInst*[alBank->count];

	for (int x = 0; x < alBank->count; x++)
	{
		alBank->inst[x] = new ALInst();
		alBank->inst[x]->samplerate = 0;
		alBank->inst[x]->sounds = NULL;
	}

	for (int x = 0; x < alBank->count; x++)
	{
		alBank->inst[x]->soundCount = 1;
		alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

		for (int y = 0; y < alBank->inst[x]->soundCount; y++)
		{
			alBank->inst[x]->sounds[y] = new ALSound();

			alBank->inst[x]->sounds[y]->hasWavePrevious = false;
			alBank->inst[x]->sounds[y]->hasWaveSecondary = false;
			alBank->inst[x]->sounds[y]->flags = 0;

			alBank->inst[x]->sounds[y]->wav.adpcmWave = NULL;
			alBank->inst[x]->sounds[y]->wav.rawWave = NULL;
			alBank->inst[x]->sounds[y]->wav.base = ctlOffset;

			CTetrisphereDecoder tetDec;
			unsigned char* tempBuffer = new unsigned char[0x100000];
			alBank->inst[x]->sounds[y]->wav.len = tetDec.sphereDecompress(&ctl[alBank->inst[x]->sounds[y]->wav.base], tempBuffer);

			alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];
			memcpy(alBank->inst[x]->sounds[y]->wav.wavData, tempBuffer, alBank->inst[x]->sounds[y]->wav.len);
			delete [] tempBuffer;
			
			if (numberInstruments == 0)
				alBank->inst[x]->sounds[y]->wav.type = AL_SIGNED_RAW8;
			else
				alBank->inst[x]->sounds[y]->wav.type = AL_SIGNED_RAW16;
		}
	}
	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioRNCN64PtrOffset(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl, unsigned long offset)
{
	unsigned char* outputDecompressed = new unsigned char[0x1000000];
	int fileSizeCompressed = -1;
	RncDecoder rnc;
	rnc.unpackM1(&ctl[ctlOffset], outputDecompressed, 0x0, fileSizeCompressed);
	unsigned long ctlSizeUncompressed = fileSizeCompressed;
	ALBank* alBank = ReadAudioN64PtrWavetableV2(&outputDecompressed[offset], ctlSizeUncompressed, 0, tbl);
	alBank->soundBankFormat = RNCCOMPRESSEDN64PTR;
	delete [] outputDecompressed;
	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioSno(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl, unsigned long expectedSize)
{
	unsigned char* outputDecompressed = new unsigned char[0x1000000];
	CSnoDecoder snoDecoder;
	snoDecoder.dec(&ctl[ctlOffset], ctlSize, expectedSize, outputDecompressed);
	ALBank* alBank = ReadAudioN64PtrWavetableV2(&outputDecompressed[0], expectedSize, 0, tbl);
	alBank->soundBankFormat = SNOW;
	delete [] outputDecompressed;
	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioRNCN64Ptr(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl)
{
	return ReadAudioRNCN64PtrOffset(ctl, ctlSize, ctlOffset, tbl, 0);
}

ALBank* CN64AIFCAudio::ReadRNCAudio(unsigned char* ROM, unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl, int bankNumber)
{
	unsigned char* outputDecompressed = new unsigned char[0x1000000];
	int fileSizeCompressed = -1;
	RncDecoder rnc;
	rnc.unpackM1(&ctl[ctlOffset], outputDecompressed, 0x0, fileSizeCompressed);
	ALBank* alBank = ReadAudio(ROM, &outputDecompressed[0], fileSizeCompressed, 0, tbl, 0, 0, bankNumber);
	alBank->soundBankFormat = STANDARDRNCCOMPRESSED;
	delete [] outputDecompressed;
	return alBank;
}

ALBank* CN64AIFCAudio::ReadRNXAudio(unsigned char* ROM, unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl, int bankNumber)
{
	unsigned char* outputDecompressedA = new unsigned char[0x1000000];
	unsigned char* outputDecompressedB = new unsigned char[0x1000000];
	int fileSizeCompressed = -1;
	RncDecoder rnc;
	int size1 = rnc.unpackM1(&ctl[ctlOffset], outputDecompressedA, 0x0, fileSizeCompressed);

	int nextCtlSpot = ctlOffset + fileSizeCompressed;
	nextCtlSpot += (8 - (fileSizeCompressed % 8));

	nextCtlSpot += 0x10;

	int size2 = rnc.unpackM1(&ctl[nextCtlSpot], outputDecompressedB, 0x0, fileSizeCompressed);

	unsigned char* outputDecompressed = new unsigned char[0x1000000];
	for (int x = 0; x < size1; x++)
	{
		outputDecompressed[x] = outputDecompressedA[x];
	}

	for (int x = 0; x < size2; x++)
	{
		outputDecompressed[x+size1] = outputDecompressedB[x];
	}

	delete [] outputDecompressedA;
	delete [] outputDecompressedB;

	ALBank* alBank = ReadAudio(ROM, &outputDecompressed[0], fileSizeCompressed, 0, tbl, 0, 0, bankNumber);
	alBank->soundBankFormat = STANDARDRNXCOMPRESSED;
	delete [] outputDecompressed;
	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioN64SN64(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl, int numberInstruments, unsigned long mask)
{
	unsigned short numberBands = 1;
	unsigned long bankOffset = ctlOffset + CharArrayToLong(&ctl[ctlOffset+0x2C]);

	// header size 0x30
	ALBank* alBank = new ALBank();
	alBank->soundBankFormat = SN64;
	alBank->count = numberInstruments;

	alBank->flags = 0x0000;
	alBank->pad = 0x0;
	alBank->samplerate = 22050;
	alBank->percussion = 0x0000;

	unsigned long numberElementsSectionOne = 0;
	for (int x = 0; x < numberInstruments; x++)
	{
		unsigned long numberCheck = (CharArrayToLong(&ctl[ctlOffset + x*4]) & mask);
		if (numberCheck > numberElementsSectionOne)
			numberElementsSectionOne = numberCheck;
	}
	numberElementsSectionOne++;

	unsigned long dataOffset = ctlOffset + (numberInstruments * 0x4);
	if ((dataOffset % 0x8) != 0)
		dataOffset += 4;

	unsigned long numberElementsSectionTwo = 0;
	for (int x = 0; x < numberElementsSectionOne; x++)
	{
		unsigned long numberCheck = (CharArrayToShort(&ctl[dataOffset + x*0x14 + 0xA]) & mask);
		if (numberCheck > numberElementsSectionTwo)
			numberElementsSectionTwo = numberCheck;
	}
	numberElementsSectionTwo++;

	dataOffset = dataOffset + (numberElementsSectionOne * 0x14);
	if ((dataOffset % 0x8) != 0)
		dataOffset += 4;

	unsigned long numberLoops = 0x00000000;
	bool foundOneLoop = false;
	for (int x = 0; x < numberElementsSectionTwo; x++)
	{
		unsigned long numberCheck = (CharArrayToLong(&ctl[dataOffset + (x * 0x18) + 0x10]));
		if (numberCheck == 0xFFFFFFFF)
			continue;
		else
			foundOneLoop = true;

		if (numberCheck > numberLoops)
		{
			numberLoops = numberCheck;
		}
	}
	if (foundOneLoop)
		numberLoops++;
	
	alBank->inst = NULL;
	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = 0;

	if ((alBank->flags == 0x0000) || (alBank->flags == 0x0100)) // offset
	{
		alBank->inst = new ALInst*[alBank->count];

		for (int x = 0; x < alBank->count; x++)
		{
			alBank->inst[x] = new ALInst();
			alBank->inst[x]->samplerate = 0;
			alBank->inst[x]->sounds = NULL;
		}

		for (int x = 0; x < alBank->count; x++)
		{
			unsigned long instrumentNumber = (CharArrayToLong(&ctl[ctlOffset + x*4]) & mask);

			alBank->inst[x]->soundCount = 1;
			alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

			for (int y = 0; y < alBank->inst[x]->soundCount; y++)
			{
				alBank->inst[x]->sounds[y] = new ALSound();
				alBank->inst[x]->sounds[y]->wav.wavData = NULL;
			}

			unsigned long dataOffset = ctlOffset + (numberInstruments * 0x4);
			if ((dataOffset % 0x8) != 0)
				dataOffset += 4;
			unsigned long dataNumber = (CharArrayToShort(&ctl[dataOffset + (instrumentNumber * 0x14)+ 0xA]) & mask);

			dataOffset = dataOffset + (numberElementsSectionOne * 0x14);
			if ((dataOffset % 0x8) != 0)
				dataOffset += 4;
			unsigned long rawDataOffset = dataOffset + (dataNumber * 0x18);

			unsigned long loopDataOffset;
			unsigned long predictorDataOffset;

			loopDataOffset = dataOffset + (numberElementsSectionTwo * 0x18) + 0x8;
			predictorDataOffset = dataOffset + (numberElementsSectionTwo * 0x18) + 0x8 + (numberLoops * 0x30);


			for (int y = 0; y < alBank->inst[x]->soundCount; y++)
			{
				alBank->inst[x]->sounds[y]->flags = 0x0000;

				if ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1))
				{
					alBank->inst[x]->sounds[y]->wav.base = CharArrayToLong(&ctl[rawDataOffset + 0x0]);
					alBank->inst[x]->sounds[y]->wav.len = CharArrayToLong(&ctl[rawDataOffset + 0x4]);
					alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];

					for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
					{
						alBank->inst[x]->sounds[y]->wav.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wav.base + r];
					}
					

					alBank->inst[x]->sounds[y]->wav.type = AL_ADPCM_WAVE;
					alBank->inst[x]->sounds[y]->wav.flags = 0x0000;
					// MUST PAD to 4s

					if ((alBank->inst[x]->sounds[y]->wav.type == AL_ADPCM_WAVE) && ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1)))
					{
						alBank->inst[x]->sounds[y]->wav.adpcmWave = new ALADPCMWaveInfo();
						
						unsigned long predictorOffset = predictorDataOffset + 0x108 * dataNumber;
						unsigned long loopOffset = CharArrayToLong(&ctl[rawDataOffset + 0x10]);

						if (loopOffset != 0xFFFFFFFF)
						{
							loopOffset = loopDataOffset + loopOffset;
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = new ALADPCMloop();
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);
							for (int z = 0; z < 0x10; z++)
							{
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffset + 0xC + z * 2]);
							}
						}
						else
						{
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = NULL;
						}

					
						if (predictorOffset != 0x00000000)
						{
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book = new ALADPCMBook();
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffset + 0x0]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffset + 0x4]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8];

							for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8; z++)
							{
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + 0x8 + z * 2]);
							}
						}
						else
						{
							MessageBox(NULL, "Error", "Missing predictors in ALSound wav", NULL);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book = NULL;
						}
					}
					else
					{
						DisposeALBank(alBank);
						MessageBox(NULL, "Error", "Unsupported type in ALSound wav", NULL);
						return NULL;
					}
				}
				else
				{
					DisposeALBank(alBank);
					MessageBox(NULL, "Error", "Unsupported type in ALSound", NULL);
					return NULL;
				}
			}
		}
	}
	else
	{
		DisposeALBank(alBank);
		MessageBox(NULL, "Error", "Unsupported type in ALBank", NULL);
		return NULL;
	}

	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioN64SN64Zlib(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl, int numberInstruments, unsigned long mask)
{
	int fileSizeCompressed = -1;
	GECompression gedecompress;
	gedecompress.SetGame(MORTALKOMBAT);
	gedecompress.SetCompressedBuffer(&ctl[ctlOffset], ctlSize);
	int fileSizeUncompressed;
	unsigned char* outputDecompressed = gedecompress.OutputDecompressedBuffer(fileSizeUncompressed, fileSizeCompressed);

	ALBank* alBank = NULL;
	if (outputDecompressed != NULL)
	{
		unsigned long fileSizeUncompressedLong = fileSizeUncompressed;
		alBank = ReadAudioN64SN64(&outputDecompressed[0], fileSizeUncompressedLong, 0, tbl, numberInstruments, mask);
		alBank->soundBankFormat = ZLIBSN64;
		delete [] outputDecompressed;
	}
	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioN64PtrWavetableBlitz(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl)
{
	unsigned char* outputDecompressed = new unsigned char[0x1000000];
	int fileSizeCompressed = -1;
	CBlitzDecoder blitzdec;
	blitzdec.dec(&ctl[ctlOffset], outputDecompressed, fileSizeCompressed);
	ALBank* alBank = ReadAudioN64PtrWavetableV2(&outputDecompressed[0], ctlSize, 0, tbl);
	alBank->soundBankFormat = N64PTRWAVETABLETABLEV2BLITZ;
	delete [] outputDecompressed;
	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioNinDec(unsigned char* ROM, unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl, int fileSizeCompressed)
{
	CNinDec ninDec;
	
	int expectedSize = ((((((ctl[ctlOffset+3] << 8) | ctl[ctlOffset+2]) << 8) | ctl[ctlOffset+1]) << 8) | ctl[ctlOffset+0]);

	unsigned char* outputDecompressed = new unsigned char[expectedSize*2]; // can go longer
	
	ninDec.dec(&ctl[ctlOffset], fileSizeCompressed, outputDecompressed);
	ALBank* alBank = ReadAudio(ROM, &outputDecompressed[0], ctlSize, 0, tbl, 0, 0, 0);
	alBank->soundBankFormat = NINDEC;
	delete [] outputDecompressed;
	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioSydney(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl, int fileSizeCompressed)
{
	SydneyDecoder decode;
	
	int expectedSize = CharArrayToLong(&ctl[ctlOffset+4]);

	unsigned char* outputDecompressed = new unsigned char[expectedSize];
	
	decode.dec(&ctl[ctlOffset+0x10], fileSizeCompressed, expectedSize, outputDecompressed);
	ALBank* alBank = ReadAudioN64PtrWavetableV2(&outputDecompressed[0], ctlSize, 0, tbl);
	alBank->soundBankFormat = SYDNEY;
	delete [] outputDecompressed;
	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioN64Titus(unsigned char* ROM, unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl)
{
	int fileSizeCompressed = -1;
	SupermanDecoder decode;
	int expectedSize = decode.header(&ctl[ctlOffset], fileSizeCompressed);
	unsigned char* outputDecompressed = new unsigned char[expectedSize];
	
	decode.dec(&ctl[ctlOffset+0x11], fileSizeCompressed, expectedSize, outputDecompressed);
	ALBank* alBank = ReadAudio(ROM, &outputDecompressed[0], ctlSize, 0, tbl, 0x0, 0x0, 0);
	alBank->soundBankFormat = TITUS;
	delete [] outputDecompressed;
	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioN64PtrWavetableV2YAY0(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl)
{
	unsigned char* outputDecompressed = new unsigned char[0x1000000];
	int fileSizeCompressed = -1;
	YAY0 yay0;
	yay0.decodeAll(&ctl[ctlOffset], outputDecompressed, fileSizeCompressed);
	ALBank* alBank = ReadAudioN64PtrWavetableV2(&outputDecompressed[0], ctlSize, 0, tbl);
	alBank->soundBankFormat = N64PTRWAVETABLETABLEV2YAY0;
	delete [] outputDecompressed;
	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioBnkB(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl)
{
	unsigned short numberBands = 1;
	int startOffset;
	if (ctl[ctlOffset+4] == 0x4)
		startOffset = 0x14;
	else if (ctl[ctlOffset+4] == 0x2)
		startOffset = 0xC;
	else
		startOffset = 0x14;
	unsigned long bankOffset = ctlOffset + startOffset;

	// header size 0x30
	ALBank* alBank = new ALBank();
	alBank->soundBankFormat = BNKB;
	alBank->count = (unsigned short)CharArrayToShort(&ctl[ctlOffset+0x6]);
	alBank->flags = 0x0000;
	alBank->pad = 0x0;
	alBank->samplerate = 8000;
	alBank->percussion = 0x000;
	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = 0;

	unsigned long tblOffset = ctlOffset + CharArrayToLong(&ctl[ctlOffset+8]);

	alBank->inst = NULL;

	if ((alBank->flags == 0x0000) || (alBank->flags == 0x0100)) // offset
	{
		alBank->inst = new ALInst*[alBank->count];

		for (int x = 0; x < alBank->count; x++)
		{
			alBank->inst[x] = new ALInst();
			alBank->inst[x]->samplerate = 0;
			alBank->inst[x]->sounds = NULL;
		}

		for (int x = 0; x < alBank->count; x++)
		{
			unsigned long offsetInstrument = CharArrayToLong(&ctl[bankOffset + x*4]);

			if (offsetInstrument == 0x0000)
			{
				alBank->inst[x]->soundCount = 0;
				alBank->inst[x]->sounds = NULL;
				continue;
			}

			offsetInstrument = bankOffset + x*4 + offsetInstrument;

			alBank->inst[x]->soundCount = 1;

			alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

			for (int y = 0; y < alBank->inst[x]->soundCount; y++)
			{
				alBank->inst[x]->sounds[y] = new ALSound();
				alBank->inst[x]->sounds[y]->wav.wavData = NULL;
			}

			for (int y = 0; y < alBank->inst[x]->soundCount; y++)
			{
				alBank->inst[x]->sounds[y]->wav.base = 0;
				unsigned long predictorOffset = 0;
				for (int z = (offsetInstrument + 2); z < (offsetInstrument + 0x100); z++)
				{
					if (CharArrayToShort(&ctl[z]) == 0x8804)
					{
						alBank->inst[x]->sounds[y]->wav.base = CharArrayToLong(&ctl[z + 2]);
						break;
					}
					else if ((CharArrayToShort(&ctl[z]) == 0x5054) || (CharArrayToLong(&ctl[z]) == 0xFF000000))
					{
						break;
					}
				}
				for (int z = (offsetInstrument + 2); z < (offsetInstrument + 0x100); z++)
				{
					if ((CharArrayToShort(&ctl[z]) == 0x8F88) && (ctl[z+2] == 0x00))
					{
						predictorOffset = z + 2;
						break;
					}
					else if ((CharArrayToShort(&ctl[z]) == 0x5054) || (CharArrayToLong(&ctl[z]) == 0xFF000000))
					{
						break;
					}
				}
				alBank->inst[x]->sounds[y]->wav.len = 0x7000;

				alBank->inst[x]->sounds[y]->wav.type = AL_ADPCM_WAVE;
				alBank->inst[x]->sounds[y]->wav.flags = 0x0000;
				// MUST PAD to 4s

				if (predictorOffset != 0x00000000)
				{
					alBank->inst[x]->sounds[y]->wav.type = AL_ADPCM_WAVE;
					alBank->inst[x]->sounds[y]->wav.adpcmWave = new ALADPCMWaveInfo();

					alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = NULL;
					alBank->inst[x]->sounds[y]->wav.adpcmWave->book = new ALADPCMBook();
					alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffset + 0x0]);
					alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffset + 0x4]);
					alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8];

					for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8; z++)
					{
						alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + 0x8 + z * 2]);
					}

					for (int z = predictorOffset + ((alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order + alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors) * 0x10); z < (predictorOffset + ((alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order + alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors) * 0x10) + 0x7C); z++)
					{
						if (CharArrayToShort(&ctl[z]) == 0x8C02)
						{
							alBank->inst[x]->sounds[y]->wav.len = CharArrayToShort(&ctl[z+2]);
							break;
						}
						else if ((CharArrayToShort(&ctl[z]) == 0x5054) || (CharArrayToLong(&ctl[z]) == 0xFF000000))
						{
							break;
						}
					}
					alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];

					for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
					{
						alBank->inst[x]->sounds[y]->wav.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wav.base + r];
					}
				}
				else
				{
					alBank->inst[x]->sounds[y]->wav.type = AL_RAW16_WAVE;
					alBank->inst[x]->sounds[y]->wav.rawWave = new ALRAWWaveInfo();
					alBank->inst[x]->sounds[y]->wav.rawWave->loop = NULL;
				
					for (int z = (offsetInstrument + 2); z < (offsetInstrument + 0x100); z++)
					{
						if (CharArrayToShort(&ctl[z]) == 0x8C02)
						{
							alBank->inst[x]->sounds[y]->wav.len = CharArrayToShort(&ctl[z+2]);
							break;
						}
						else if ((CharArrayToShort(&ctl[z]) == 0x5054) || (CharArrayToLong(&ctl[z]) == 0xFF000000))
						{
							break;
						}
					}
					alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];

					for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
					{
						alBank->inst[x]->sounds[y]->wav.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wav.base + r];
					}
				}
			}
		}
	}
	else
	{
		DisposeALBank(alBank);
		MessageBox(NULL, "Error", "Unsupported type in ALBank", NULL);
		return NULL;
	}

	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioN64MKMythologies(unsigned char* ROM, unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl, unsigned long uncompressedSize)
{
	unsigned char* outputDecompressed = new unsigned char[0x1000000];
	int fileSizeCompressed = -1;
	CMKMythologiesDecode compression;
	compression.dec(&ctl[ctlOffset], fileSizeCompressed, uncompressedSize, outputDecompressed);
	ALBank* alBank = ReadAudio(ROM, &outputDecompressed[0], ctlSize, 0, tbl, 0x0, 0x0, 0);
	alBank->soundBankFormat = MKMYTHOLOGIES;
	delete [] outputDecompressed;
	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioArmyMenCompressed(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl, bool littleEndianCompressedHeader, bool sarge2style)
{
	unsigned char* outputDecompressed = new unsigned char[0x1000000];
	int fileSizeCompressed = -1;
	n643docompression compression;
	compression.dec(&ctl[ctlOffset], compression.uncompressedSize(&ctl[ctlOffset], littleEndianCompressedHeader), outputDecompressed, fileSizeCompressed, littleEndianCompressedHeader, sarge2style);
	ALBank* alBank = ReadAudioN64PtrWavetableV2(&outputDecompressed[0], ctlSize, 0, tbl);
	alBank->soundBankFormat = ARMYMENFORMAT;
	delete [] outputDecompressed;
	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioMegamanN64PtrWavetableV2(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl)
{
	if (CharArrayToLong(&ctl[ctlOffset]) == 0x4E363420)
	{
		return ReadAudioN64PtrWavetableV2(ctl, ctlSize, ctlOffset, tbl);
	}
	else
	{
		unsigned char* outputDecompressed = new unsigned char[0x1000000];
		int fileSizeCompressed = -1;
		MidwayLZ compression;
		ctlSize = compression.decLZSS0B(&ctl[ctlOffset], fileSizeCompressed, outputDecompressed);
		ALBank* alBank = ReadAudioN64PtrWavetableV2(&outputDecompressed[0], ctlSize, 0, tbl);
		alBank->soundBankFormat = MEGAMAN64PTRV2;
		delete [] outputDecompressed;
		return alBank;
	}
}

ALBank* CN64AIFCAudio::ReadAudioTazN64PtrWavetableV2(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl)
{
	CString inTempFileName;
	inTempFileName.Format("tempASAS%08X.mus", ctlOffset);

	CString outTempFileName;
	outTempFileName.Format("tempASAS%08X.musb", ctlOffset);

	::DeleteFile(inTempFileName);
	::DeleteFile(outTempFileName);

	FILE* outTempIn = fopen(inTempFileName, "wb");
	if (outTempIn == NULL)
	{
		return NULL;
	}
	unsigned long expectedSize = CharArrayToLong(&ctl[ctlOffset+4]) - 0x14;
	fwrite(&expectedSize, 1, 4, outTempIn);
	fwrite(&ctl[ctlOffset+0x14], 1, ctlSize-0x14, outTempIn);
	fflush(outTempIn);
	fclose(outTempIn);

	flzh huffman;
	huffman.infile = fopen(inTempFileName, "rb");
	if (huffman.infile == NULL)
	{
		::DeleteFile(inTempFileName);
		return NULL;
	}

	huffman.outfile = fopen(outTempFileName, "wb");
	if (huffman.outfile == NULL)
	{
		return NULL;
	}

	huffman.Decode();

	fflush(huffman.outfile);
	fclose(huffman.infile);
	fclose(huffman.outfile);

	ctlSize = GetSizeFile(outTempFileName);

	FILE* inTempIn = fopen(outTempFileName, "rb");
	if (inTempIn == NULL)
	{
		return NULL;
	}
	
	unsigned char* outputDecompressed = new unsigned char[ctlSize];
	fread(outputDecompressed, 1, ctlSize, inTempIn);

	fclose(inTempIn);

	ALBank* alBank = ReadAudioN64PtrWavetableV2(&outputDecompressed[0], ctlSize, 0, tbl);
	alBank->soundBankFormat = TAZHUFFMAN;
	delete [] outputDecompressed;

	::DeleteFile(inTempFileName);
	::DeleteFile(outTempFileName);
	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioPaperMario(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl)
{
	ALBank* alBank = new ALBank();
	alBank->soundBankFormat = PAPERMARIO;
	alBank->flags = 0x0000;
	alBank->pad = 0x0;
	alBank->samplerate = 22050;
	alBank->percussion = 0x000;
	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = 0;

	unsigned long bankSize = CharArrayToLong(&ctl[ctlOffset + 4]);
	alBank->bankName.Format("%s", &ctl[ctlOffset + 0x8]);

	alBank->count = 0;
	for (int x = 0x12; x < 0x32; x+=2)
	{
		unsigned short instrumentOffset = CharArrayToShort(&ctl[ctlOffset + x]);
		if (instrumentOffset == 0x0000)
			break;

		alBank->count++;
	}

	if ((alBank->flags == 0x0000) || (alBank->flags == 0x0100)) // offset
	{
		alBank->inst = new ALInst*[alBank->count];

		for (int x = 0; x < alBank->count; x++)
		{
			alBank->inst[x] = new ALInst();
			alBank->inst[x]->samplerate = 0;
			alBank->inst[x]->sounds = NULL;
		}

		for (int x = 0; x < alBank->count; x++)
		{
			unsigned long offsetInstrument = ctlOffset + CharArrayToShort(&ctl[ctlOffset + 0x12 + (x * 2)]);

			if (offsetInstrument == 0x0000)
			{
				alBank->inst[x]->soundCount = 0;
				alBank->inst[x]->sounds = NULL;
				continue;
			}
			
			if ((alBank->inst[x]->flags == 0x0) || (alBank->inst[x]->flags == 0x1))
			{	
				alBank->inst[x]->soundCount = 1;

				alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

				for (int y = 0; y < alBank->inst[x]->soundCount; y++)
				{
					alBank->inst[x]->sounds[y] = new ALSound();
					alBank->inst[x]->sounds[y]->wav.wavData = NULL;
				}

				for (int y = 0; y < alBank->inst[x]->soundCount; y++)
				{
					alBank->inst[x]->sounds[y]->flags = 0x0000;

					if ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1))
					{
						alBank->inst[x]->sounds[y]->wav.base = CharArrayToLong(&ctl[offsetInstrument + 0x0]);
						alBank->inst[x]->sounds[y]->wav.len = CharArrayToLong(&ctl[offsetInstrument + 0x4]);
						alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];

						for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
						{
							alBank->inst[x]->sounds[y]->wav.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wav.base + r];
						}
						

						alBank->inst[x]->sounds[y]->wav.type = AL_ADPCM_WAVE;
						alBank->inst[x]->sounds[y]->wav.flags = 0x0000;
						// MUST PAD to 4s

						if ((alBank->inst[x]->sounds[y]->wav.type == AL_ADPCM_WAVE) && ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1)))
						{
							alBank->inst[x]->sounds[y]->wav.adpcmWave = new ALADPCMWaveInfo();
							
							unsigned long predictorOffset = CharArrayToLong(&ctl[offsetInstrument + 0x18]);
							unsigned long loopOffset = 0;//CharArrayToLong(&ctl[offsetInstrument + 0xC]);

							if (loopOffset != 0)
							{
								if (alBank->inst[x]->sounds[y]->flags == 0x1)
									loopOffset = loopOffset & 0xFFFFFF;
								else
									loopOffset = ctlOffset + loopOffset;

								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = new ALADPCMloop();
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);
								for (int z = 0; z < 0x10; z++)
								{
									alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffset + 0xC + z * 2]);
								}
							}
							else
							{
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = NULL;
							}

						
							if (predictorOffset != 0x00000000)
							{
								if (alBank->inst[x]->sounds[y]->flags == 0x1)
									predictorOffset = predictorOffset & 0xFFFFFF;
								else
									predictorOffset = ctlOffset + predictorOffset;

								alBank->inst[x]->sounds[y]->wav.adpcmWave->book = new ALADPCMBook();
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order = 2;
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors = 1;
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8];

								for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8; z++)
								{
									alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + z * 2]);
								}
							}
							else
							{
								MessageBox(NULL, "Error", "Missing predictors in ALSound wav", NULL);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book = NULL;
							}
						}
						else
						{
							DisposeALBank(alBank);
							MessageBox(NULL, "Error", "Unsupported type in ALSound wav", NULL);
							return NULL;
						}
					}
					else
					{
						DisposeALBank(alBank);
						MessageBox(NULL, "Error", "Unsupported type in ALSound", NULL);
						return NULL;
					}
				}
			}
			else
			{
				DisposeALBank(alBank);
				MessageBox(NULL, "Error", "Unsupported inst type in ALInst", NULL);
				return NULL;
			}
		}
	}
	else
	{
		DisposeALBank(alBank);
		MessageBox(NULL, "Error", "Unsupported type in ALBank", NULL);
		return NULL;
	}

	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioB0(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl)
{
	ALBank* alBank = new ALBank();
	alBank->soundBankFormat = B0;
	alBank->flags = 0x0000;
	alBank->pad = 0x0;
	alBank->samplerate = 22050;
	alBank->percussion = 0x000;
	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = 0;

	alBank->count = 1;

	unsigned long bankOffset = ctlOffset;

	int soundCount = CharArrayToLong(&ctl[bankOffset]) / 0x10;

	alBank->inst = NULL;

	if ((alBank->flags == 0x0000) || (alBank->flags == 0x0100)) // offset
	{
		alBank->inst = new ALInst*[alBank->count];

		for (int x = 0; x < alBank->count; x++)
		{
			alBank->inst[x] = new ALInst();
			alBank->inst[x]->samplerate = 0;
			alBank->inst[x]->sounds = NULL;
		}

		int x = 0;
		{
			alBank->inst[x]->soundCount = soundCount;
			alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

			for (int y = 0; y < alBank->inst[x]->soundCount; y++)
			{
				alBank->inst[x]->sounds[y] = new ALSound();
				alBank->inst[x]->sounds[y]->wav.wavData = NULL;
			}

			for (int y = 0; y < alBank->inst[x]->soundCount; y++)
			{
				unsigned long offsetSound = bankOffset + (0x10 * y);

				alBank->inst[x]->sounds[y]->samplePan = ctl[offsetSound+0xC];
				alBank->inst[x]->sounds[y]->sampleVolume = ctl[offsetSound+0xD];
				alBank->inst[x]->sounds[y]->flags = ctl[offsetSound+0xE];

				
				if ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1))
				{
					unsigned long offsetEnv = CharArrayToLong(&ctl[offsetSound+ 0x0]);
					offsetEnv = bankOffset + offsetEnv;

					alBank->inst[x]->sounds[y]->env.attackTime = CharArrayToLong(&ctl[offsetEnv + 0x0]);
					alBank->inst[x]->sounds[y]->env.decayTime = CharArrayToLong(&ctl[offsetEnv + 0x4]);
					alBank->inst[x]->sounds[y]->env.releaseTime = CharArrayToLong(&ctl[offsetEnv + 0x8]);
					alBank->inst[x]->sounds[y]->env.attackVolume = ctl[offsetEnv + 0xC];
					alBank->inst[x]->sounds[y]->env.decayVolume = ctl[offsetEnv + 0xD];
					alBank->inst[x]->sounds[y]->env.zeroPad = CharArrayToShort(&ctl[offsetEnv + 0xE]);



					unsigned long offsetWaveTable = CharArrayToLong(&ctl[offsetSound+ 0x8]);
					offsetWaveTable = bankOffset + offsetWaveTable;

					unsigned char flag = CharArrayToLong(&ctl[offsetWaveTable + 0x0]) >> 24; // hack for NUD-DSCJ-JPN, can't imagine impact others
					if (flag == 0x40) // Means using 64DD IPL Bank
						alBank->inst[x]->sounds[y]->wav.base = (CharArrayToLong(&ctl[offsetWaveTable + 0x0]) & 0xFFFFFF) + 0x140000;
					else
						alBank->inst[x]->sounds[y]->wav.base = CharArrayToLong(&ctl[offsetWaveTable + 0x0]);
					alBank->inst[x]->sounds[y]->wav.len = CharArrayToLong(&ctl[offsetWaveTable + 0x4]);
					alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];

					for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
					{
						alBank->inst[x]->sounds[y]->wav.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wav.base + r];
					}
					

					alBank->inst[x]->sounds[y]->wav.type = ctl[offsetWaveTable + 0x8];
					alBank->inst[x]->sounds[y]->wav.flags = ctl[offsetWaveTable + 0x9];
					// MUST PAD to 4s

					if ((alBank->inst[x]->sounds[y]->wav.type == AL_ADPCM_WAVE) && ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1)))
					{
						alBank->inst[x]->sounds[y]->wav.adpcmWave = new ALADPCMWaveInfo();
						unsigned long loopOffset = CharArrayToLong(&ctl[offsetWaveTable + 0xC]);
						unsigned long predictorOffset = CharArrayToLong(&ctl[offsetWaveTable + 0x10]);

						if (loopOffset != 0)
						{
							loopOffset = bankOffset + loopOffset;

							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = new ALADPCMloop();
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);
							for (int z = 0; z < 0x10; z++)
							{
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffset + 0xC + z * 2]);
							}
						}
						else
						{
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = NULL;
						}

						if (predictorOffset != 0)
						{
							predictorOffset = bankOffset + predictorOffset;

							alBank->inst[x]->sounds[y]->wav.adpcmWave->book = new ALADPCMBook();
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffset + 0x0]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffset + 0x4]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8];

							for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8; z++)
							{
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + 0x8 + z * 2]);
							}
						}
					}
					else if ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1))
					{
						alBank->inst[x]->sounds[y]->wav.rawWave = new ALRAWWaveInfo();
						unsigned long loopOffset = CharArrayToLong(&ctl[offsetWaveTable + 0xC]);

						if (loopOffset != 0)
						{
							loopOffset = bankOffset + loopOffset;

							alBank->inst[x]->sounds[y]->wav.rawWave->loop = new ALRawLoop();
							alBank->inst[x]->sounds[y]->wav.rawWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
							alBank->inst[x]->sounds[y]->wav.rawWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
							alBank->inst[x]->sounds[y]->wav.rawWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);	
						}
						else
						{
							alBank->inst[x]->sounds[y]->wav.rawWave->loop = NULL;
						}
					}
					else
					{
						DisposeALBank(alBank);
						MessageBox(NULL, "Error", "Unsupported type in ALSound wav", NULL);
						return NULL;
					}
				}
				else
				{
					DisposeALBank(alBank);
					MessageBox(NULL, "Error", "Unsupported type in ALSound", NULL);
					return NULL;
				}
			}
		}
	}
	else
	{
		DisposeALBank(alBank);
		MessageBox(NULL, "Error", "Unsupported type in ALBank", NULL);
		return NULL;
	}

	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioDuckDodgers(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl)
{
	ALBank* alBank = new ALBank();
	alBank->soundBankFormat = DUCKDODGERS;
	alBank->flags = 0x0000;
	alBank->pad = 0x0;
	alBank->samplerate = 22050;
	alBank->percussion = 0x000;
	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = 0;

	unsigned long bankSize = CharArrayToLong(&ctl[ctlOffset + 4]);
	alBank->bankName.Format("%s", &ctl[ctlOffset + 0x8]);

	alBank->count = CharArrayToLong(&ctl[ctlOffset + 0xC]);

	if ((alBank->flags == 0x0000) || (alBank->flags == 0x0100)) // offset
	{
		alBank->inst = new ALInst*[alBank->count];

		for (int x = 0; x < alBank->count; x++)
		{
			alBank->inst[x] = new ALInst();
			alBank->inst[x]->samplerate = 0;
			alBank->inst[x]->sounds = NULL;
		}

		for (int x = 0; x < alBank->count; x++)
		{
			unsigned long offsetInstrument = ctlOffset + 0x10 + (0x18 * x);

			if (offsetInstrument == 0x0000)
			{
				alBank->inst[x]->soundCount = 0;
				alBank->inst[x]->sounds = NULL;
				continue;
			}
			
			if ((alBank->inst[x]->flags == 0x0) || (alBank->inst[x]->flags == 0x1))
			{	
				alBank->inst[x]->soundCount = 1;

				alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

				for (int y = 0; y < alBank->inst[x]->soundCount; y++)
				{
					alBank->inst[x]->sounds[y] = new ALSound();
					alBank->inst[x]->sounds[y]->wav.wavData = NULL;
				}

				for (int y = 0; y < alBank->inst[x]->soundCount; y++)
				{
					alBank->inst[x]->sounds[y]->flags = 0x0000;

					if ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1))
					{
						alBank->inst[x]->samplerate = CharArrayToLong(&ctl[offsetInstrument + 0x10]);

						alBank->inst[x]->sounds[y]->wav.base = CharArrayToLong(&ctl[offsetInstrument + 0xC]) + 0xA0;
						alBank->inst[x]->sounds[y]->wav.len = CharArrayToLong(&ctl[offsetInstrument + 0x0]);
						alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];

						for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
						{
							alBank->inst[x]->sounds[y]->wav.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wav.base + r];
						}
						

						alBank->inst[x]->sounds[y]->wav.type = AL_ADPCM_WAVE;
						alBank->inst[x]->sounds[y]->wav.flags = 0x0000;
						// MUST PAD to 4s

						if ((alBank->inst[x]->sounds[y]->wav.type == AL_ADPCM_WAVE) && ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1)))
						{
							alBank->inst[x]->sounds[y]->wav.adpcmWave = new ALADPCMWaveInfo();
							
							unsigned long predictorOffset = CharArrayToLong(&ctl[offsetInstrument + 0xC]) + 0x20;
							unsigned long loopOffset = 0;//CharArrayToLong(&ctl[offsetInstrument + 0xC]);

							if (loopOffset != 0)
							{
								if (alBank->inst[x]->sounds[y]->flags == 0x1)
									loopOffset = loopOffset & 0xFFFFFF;
								else
									loopOffset = ctlOffset + loopOffset;

								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = new ALADPCMloop();
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);
								for (int z = 0; z < 0x10; z++)
								{
									alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffset + 0xC + z * 2]);
								}
							}
							else
							{
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = NULL;
							}

						
							if (predictorOffset != 0x00000000)
							{
								if (alBank->inst[x]->sounds[y]->flags == 0x1)
									predictorOffset = predictorOffset & 0xFFFFFF;
								else
									predictorOffset = ctlOffset + predictorOffset;

								alBank->inst[x]->sounds[y]->wav.adpcmWave->book = new ALADPCMBook();
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order = 2;
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors = 4;
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8];

								for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8; z++)
								{
									alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + z * 2]);
								}
							}
							else
							{
								MessageBox(NULL, "Error", "Missing predictors in ALSound wav", NULL);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book = NULL;
							}
						}
						else
						{
							DisposeALBank(alBank);
							MessageBox(NULL, "Error", "Unsupported type in ALSound wav", NULL);
							return NULL;
						}
					}
					else
					{
						DisposeALBank(alBank);
						MessageBox(NULL, "Error", "Unsupported type in ALSound", NULL);
						return NULL;
					}
				}
			}
			else
			{
				DisposeALBank(alBank);
				MessageBox(NULL, "Error", "Unsupported inst type in ALInst", NULL);
				return NULL;
			}
		}
	}
	else
	{
		DisposeALBank(alBank);
		MessageBox(NULL, "Error", "Unsupported type in ALBank", NULL);
		return NULL;
	}

	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioN64PtrWavetableV2(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl)
{
	unsigned short numberBands = 1;
	unsigned long bankOffset = ctlOffset + CharArrayToLong(&ctl[ctlOffset+0x2C]);

	// header size 0x30
	ALBank* alBank = new ALBank();
	alBank->soundBankFormat = N64PTRWAVETABLETABLEV2;
	alBank->count = (unsigned short)CharArrayToLong(&ctl[ctlOffset+0x20]);
	unsigned long endOffsets = ctlOffset + CharArrayToLong(&ctl[ctlOffset+0x24]);
	unsigned long endExtraBytes = ctlOffset + CharArrayToLong(&ctl[ctlOffset + 0x28]);
	ctlSize = CharArrayToLong(&ctl[ctlOffset + 0x28]);
	alBank->flags = 0x0000;
	alBank->pad = 0x0;
	alBank->samplerate = 22050;
	alBank->percussion = 0x000;
	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = 0;

	alBank->bankName.Format("%s", &ctl[ctlOffset + 0x14]);
	
	alBank->inst = NULL;

	if ((alBank->flags == 0x0000) || (alBank->flags == 0x0100)) // offset
	{
		alBank->inst = new ALInst*[alBank->count];

		for (int x = 0; x < alBank->count; x++)
		{
			alBank->inst[x] = new ALInst();
			alBank->inst[x]->samplerate = 0;
			alBank->inst[x]->sounds = NULL;
		}

		for (int x = 0; x < alBank->count; x++)
		{
			unsigned long offsetInstrument = CharArrayToLong(&ctl[bankOffset + x*4]);
			if (offsetInstrument == 0x0000)
			{
				alBank->inst[x]->soundCount = 0;
				alBank->inst[x]->sounds = NULL;
				continue;
			}

			if (alBank->flags == 0x0100)
				offsetInstrument = offsetInstrument & 0xFFFFFF;
			else
				offsetInstrument = ctlOffset + offsetInstrument;

			if ((alBank->inst[x]->flags == 0x0) || (alBank->inst[x]->flags == 0x1))
			{	
				alBank->inst[x]->soundCount = 1;

				alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

				for (int y = 0; y < alBank->inst[x]->soundCount; y++)
				{
					alBank->inst[x]->sounds[y] = new ALSound();
					alBank->inst[x]->sounds[y]->wav.wavData = NULL;
				}

				for (int y = 0; y < alBank->inst[x]->soundCount; y++)
				{
					alBank->inst[x]->sounds[y]->flags = 0x0000;

					if ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1))
					{
						alBank->inst[x]->sounds[y]->wav.base = CharArrayToLong(&ctl[offsetInstrument + 0x0]);
						alBank->inst[x]->sounds[y]->wav.len = CharArrayToLong(&ctl[offsetInstrument + 0x4]);
						alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];

						for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
						{
							alBank->inst[x]->sounds[y]->wav.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wav.base + r];
						}
						

						alBank->inst[x]->sounds[y]->wav.type = AL_ADPCM_WAVE;
						alBank->inst[x]->sounds[y]->wav.flags = 0x0000;
						// MUST PAD to 4s

						if ((alBank->inst[x]->sounds[y]->wav.type == AL_ADPCM_WAVE) && ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1)))
						{
							alBank->inst[x]->sounds[y]->wav.adpcmWave = new ALADPCMWaveInfo();
							
							unsigned long predictorOffset = CharArrayToLong(&ctl[offsetInstrument + 0x10]);
							unsigned long loopOffset = CharArrayToLong(&ctl[offsetInstrument + 0xC]);

							if (loopOffset != 0)
							{
								if (alBank->inst[x]->sounds[y]->flags == 0x1)
									loopOffset = loopOffset & 0xFFFFFF;
								else
									loopOffset = ctlOffset + loopOffset;

								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = new ALADPCMloop();
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);
								for (int z = 0; z < 0x10; z++)
								{
									alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffset + 0xC + z * 2]);
								}
							}
							else
							{
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = NULL;
							}

						
							if (predictorOffset != 0x00000000)
							{
								if (alBank->inst[x]->sounds[y]->flags == 0x1)
									predictorOffset = predictorOffset & 0xFFFFFF;
								else
									predictorOffset = ctlOffset + predictorOffset;

								alBank->inst[x]->sounds[y]->wav.adpcmWave->book = new ALADPCMBook();
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffset + 0x0]);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffset + 0x4]);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8];

								for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8; z++)
								{
									alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + 0x8 + z * 2]);
								}
							}
							else
							{
								MessageBox(NULL, "Error", "Missing predictors in ALSound wav", NULL);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book = NULL;
							}
						}
						else
						{
							DisposeALBank(alBank);
							MessageBox(NULL, "Error", "Unsupported type in ALSound wav", NULL);
							return NULL;
						}
					}
					else
					{
						DisposeALBank(alBank);
						MessageBox(NULL, "Error", "Unsupported type in ALSound", NULL);
						return NULL;
					}
				}
			}
			else
			{
				DisposeALBank(alBank);
				MessageBox(NULL, "Error", "Unsupported inst type in ALInst", NULL);
				return NULL;
			}
		}

		for (int x = 0; x < alBank->count; x++)
		{
			alBank->inst[x]->volume = ctl[endOffsets + x];
		}
	}
	else
	{
		DisposeALBank(alBank);
		MessageBox(NULL, "Error", "Unsupported type in ALBank", NULL);
		return NULL;
	}

	return alBank;
}


ALBank* CN64AIFCAudio::ReadAudioFZero(unsigned char* ctl, int ctlSize, int ctlOffset, unsigned char* tbl, int instrumentCount, unsigned char* rom)
{
	ALBank* alBank = new ALBank();

	unsigned short numberBands = 1;
	unsigned long bankOffset = 0;

	alBank->count = instrumentCount;
	alBank->soundBankFormat = FZEROFORMAT;
	alBank->flags = 0x0000;
	alBank->pad = 0x0000;
	alBank->samplerate = 11025;
	alBank->percussion = 0x0000;
	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = 0;

	alBank->inst = NULL;

	if ((alBank->flags == 0x0000) || (alBank->flags == 0x0100)) // offset
	{
		alBank->inst = new ALInst*[alBank->count];

		for (int x = 0; x < alBank->count; x++)
		{
			alBank->inst[x] = new ALInst();
			alBank->inst[x]->samplerate = 0;
			alBank->inst[x]->sounds = NULL;
		}

		for (int x = 0; x < alBank->count; x++)
		{
			unsigned long offsetInstrument = CharArrayToLong(&ctl[ctlOffset + x*4 + 0x4]);

			if (offsetInstrument == 0x0000)
			{
				alBank->inst[x]->soundCount = 0;
				alBank->inst[x]->sounds = NULL;
				continue;
			}

			if (alBank->flags == 0x0100)
				offsetInstrument = offsetInstrument & 0xFFFFFF;
			else
				offsetInstrument = ctlOffset + offsetInstrument;
		
			unsigned long offsetSound1 = CharArrayToLong(&ctl[offsetInstrument + 0x10]);
			unsigned long offsetSound2 = CharArrayToLong(&ctl[offsetInstrument + 0x10 + 0x8]);

			alBank->inst[x]->soundCount = 1;
			if (offsetSound2 != 0x00000000)
				alBank->inst[x]->soundCount++;

			alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

			for (int y = 0; y < alBank->inst[x]->soundCount; y++)
			{
				alBank->inst[x]->sounds[y] = new ALSound();
				alBank->inst[x]->sounds[y]->wav.wavData = NULL;
			}

			for (int y = 0; y < alBank->inst[x]->soundCount; y++)
			{
				unsigned long offsetSound;
				if (y == 0)
					offsetSound = ctlOffset + offsetSound1;
				else
					offsetSound = ctlOffset + offsetSound2;

				alBank->inst[x]->sounds[y]->env.attackVolume = CharArrayToShort(&ctl[offsetInstrument + 0x2]);
				alBank->inst[x]->sounds[y]->env.decayVolume = CharArrayToShort(&ctl[offsetInstrument + 0x0]);
				//alBank->inst[x]->samplerate = CharArrayToLong(&ctl[offsetInstrument + 0x4]);

				alBank->inst[x]->sounds[y]->wav.base = CharArrayToLong(&ctl[offsetSound + 0x4]);
				alBank->inst[x]->sounds[y]->wav.len = CharArrayToLong(&ctl[offsetSound + 0x0]) & 0xFFFFFF;

				if (ctl[offsetSound] != 0)
				{
					// Lots of flags here, what is this? Maybe choose Tbl A vs Tbl B on Bank 0?
				}

				alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];

				for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
				{
					alBank->inst[x]->sounds[y]->wav.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wav.base + r];
				}
				
				alBank->inst[x]->sounds[y]->wav.type == AL_ADPCM_WAVE;
				alBank->inst[x]->sounds[y]->wav.flags = 0x00;

				alBank->inst[x]->sounds[y]->wav.adpcmWave = new ALADPCMWaveInfo();

				unsigned long predictorOffset = CharArrayToLong(&ctl[offsetSound + 0xC]);
				if (predictorOffset != 0)
				{
					if (alBank->inst[x]->sounds[y]->flags == 0x1)
						predictorOffset = predictorOffset & 0xFFFFFF;
					else
						predictorOffset = ctlOffset + predictorOffset;

					alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = NULL;

					alBank->inst[x]->sounds[y]->wav.adpcmWave->book = new ALADPCMBook();
					alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffset + 0x0]);
					alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffset + 0x4]);
					alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8];

					for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8; z++)
					{
						alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + 0x8 + z * 2]);
					}
				}

				unsigned long loopOffset = CharArrayToLong(&ctl[offsetSound + 0x8]);
				if (loopOffset != 0)
				{
					if (alBank->inst[x]->sounds[y]->flags == 0x1)
						loopOffset = loopOffset & 0xFFFFFF;
					else
						loopOffset = ctlOffset + loopOffset;

					alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = new ALADPCMloop();
					alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
					alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
					alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);
					for (int z = 0; z < 0x10; z++)
					{
						alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffset + 0xC + z * 2]);
					}
				}
				else
				{
					alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = NULL;
				}
			}
		}
	}

	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioZelda(unsigned char* ctl, int ctlSize, int ctlOffset, unsigned char* tbl, int instrumentCount, unsigned long endSpot, unsigned char* rom)
{
	/*static int bankNumber = 0;
	FILE* outA = fopen("C:\\temp\\keyparse.txt", "a");
	fprintf(outA, "\n\nBank:%02X\n", bankNumber++);
	fclose(outA);*/
	ALBank* alBank = new ALBank();

	unsigned short numberBands = 1;
	unsigned long bankOffset = 0;

	unsigned long offsetInstrumentSection1 = CharArrayToLong(&ctl[ctlOffset]);
	unsigned long offsetInstrumentSection2 = CharArrayToLong(&ctl[ctlOffset + 4]);
	unsigned long endOffsetInstrument1Section1;
	unsigned long endOffsetInstrument1Section2;

	int instrumentCountNormal = instrumentCount;
	int instrumentCountSection1 = 0;
	int instrumentCountSection2 = 0;

	if (offsetInstrumentSection1 != NULL)
	{
		if (offsetInstrumentSection2 != NULL)
		{
			endOffsetInstrument1Section1 = offsetInstrumentSection2;
			endOffsetInstrument1Section2 = endSpot - ctlOffset;

			instrumentCountSection1 = ((endOffsetInstrument1Section1 - offsetInstrumentSection1) / 4);
			instrumentCountSection2 = ((endOffsetInstrument1Section2 - offsetInstrumentSection2) / 8);
		}
		else
		{
			endOffsetInstrument1Section1 = endSpot - ctlOffset;

			instrumentCountSection1 = ((endOffsetInstrument1Section1 - offsetInstrumentSection1) / 4);
		}
		
		// Make all percussion in bank 1 percussion instrument
	}
	else if (offsetInstrumentSection2 != NULL)
	{
		endOffsetInstrument1Section2 = endSpot - ctlOffset;
		instrumentCountSection2 = ((endOffsetInstrument1Section2 - offsetInstrumentSection2) / 8);
	}

	alBank->count = instrumentCount + instrumentCountSection2;
	alBank->soundBankFormat = ZELDAFORMAT;
	alBank->flags = 0x0000;
	alBank->pad = 0x0000;
	alBank->samplerate = 32000;
	alBank->percussion = 0x0000;

	alBank->inst = NULL;
	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = instrumentCountSection1;
	if (alBank->countEADPercussion > 0)
	{
		alBank->eadPercussion = new EADPercussion[alBank->countEADPercussion];
	}
	else
	{
		alBank->eadPercussion = NULL;
	}

	alBank->countSfx = instrumentCountSection2;
	if (alBank->countSfx > 0)
	{
		alBank->alSfx = new ALWave*[alBank->countSfx];
	}
	else
	{
		alBank->alSfx = NULL;
	}

	if ((alBank->flags == 0x0000) || (alBank->flags == 0x0100)) // offset
	{
		alBank->inst = new ALInst*[alBank->count];

		for (int x = 0; x < alBank->count; x++)
		{
			alBank->inst[x] = new ALInst();
			alBank->inst[x]->samplerate = 0;
			alBank->inst[x]->sounds = NULL;
		}

		for (int x = 0; x < instrumentCountNormal + instrumentCountSection1 + instrumentCountSection2; x++)
		{
			if (x < instrumentCountNormal)
			{
				unsigned long offsetInstrument = CharArrayToLong(&ctl[ctlOffset + x*4 + 0x8]);
				if (offsetInstrument == 0x0000)
				{
					alBank->inst[x]->soundCount = 0;
					alBank->inst[x]->sounds = NULL;
					continue;
				}
				offsetInstrument = ctlOffset + offsetInstrument;
				
				alBank->inst[x]->soundCount = 1;

				alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

				for (int y = 0; y < alBank->inst[x]->soundCount; y++)
				{
					alBank->inst[x]->sounds[y] = new ALSound();
					alBank->inst[x]->sounds[y]->wav.wavData = NULL;
				}

				for (int y = 0; y < alBank->inst[x]->soundCount; y++)
				{
					unsigned long offsetSoundData = offsetInstrument;

					alBank->inst[x]->sounds[y]->unknown1 = CharArrayToLong(&ctl[offsetInstrument + 0x0]);
					alBank->inst[x]->sounds[y]->floatKeyBasePrev = CharArrayToLong(&ctl[offsetInstrument + 0xC]);
					alBank->inst[x]->sounds[y]->floatKeyBase = CharArrayToLong(&ctl[offsetInstrument + 0x14]);
					alBank->inst[x]->sounds[y]->floatKeyBaseSec = CharArrayToLong(&ctl[offsetInstrument + 0x1C]);
					unsigned long offsetADRSData = CharArrayToLong(&ctl[offsetInstrument + 0x4]);
					if (offsetADRSData != 0)
					{
						offsetADRSData = ctlOffset + offsetADRSData;

						for (int z = 0; z < 8; z++)
						{
							alBank->inst[x]->sounds[y]->adsrEAD[z] = CharArrayToShort(&ctl[offsetADRSData + z*2]);
						}
					}


					unsigned long offsetWaveTable = CharArrayToLong(&ctl[offsetSoundData+ 0x10]);
					offsetWaveTable = ctlOffset + offsetWaveTable;

					alBank->inst[x]->sounds[y]->wav.base = CharArrayToLong(&ctl[offsetWaveTable + 0x4]);
					alBank->inst[x]->sounds[y]->wav.len = CharArrayToLong(&ctl[offsetWaveTable + 0x0]) & 0xFFFFFF;

					if (ctl[offsetWaveTable] == 0x30)
					{
						//30 special somehow
						alBank->inst[x]->sounds[y]->wav.decode8Only = true;
					}
					alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];

					for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
					{
						alBank->inst[x]->sounds[y]->wav.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wav.base + r];
					}
					
					alBank->inst[x]->sounds[y]->wav.type = AL_ADPCM_WAVE;
					alBank->inst[x]->sounds[y]->wav.flags = 0;
					// MUST PAD to 4s

					if ((alBank->inst[x]->sounds[y]->wav.type == AL_ADPCM_WAVE) && ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1)))
					{
						alBank->inst[x]->sounds[y]->wav.adpcmWave = new ALADPCMWaveInfo();
						unsigned long loopOffset = CharArrayToLong(&ctl[offsetWaveTable + 0x8]);
						unsigned long predictorOffset = CharArrayToLong(&ctl[offsetWaveTable + 0xC]);

						if (loopOffset != 0)
						{
							loopOffset = ctlOffset + loopOffset;

							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = new ALADPCMloop();
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->unknown1 = CharArrayToLong(&ctl[loopOffset + 0xC]);

							if (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start != 0)
							{
								for (int z = 0; z < 0x10; z++)
								{
									alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffset + 0x10 + z * 2]);
								}
							}
						}
						else
						{
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = NULL;
						}

						if (predictorOffset != 0)
						{
							predictorOffset = ctlOffset + predictorOffset;

							alBank->inst[x]->sounds[y]->wav.adpcmWave->book = new ALADPCMBook();
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffset + 0x0]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffset + 0x4]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8];

							for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8; z++)
							{
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + 0x8 + z * 2]);
							}
						}
					}


					unsigned long offsetWaveTableSecondary = CharArrayToLong(&ctl[offsetSoundData+ 0x18]);
					if (offsetWaveTableSecondary == 0x00000000)
						alBank->inst[x]->sounds[y]->hasWaveSecondary = false;
					else
					{
						alBank->inst[x]->sounds[y]->hasWaveSecondary = true;
						offsetWaveTableSecondary = ctlOffset + offsetWaveTableSecondary;

						alBank->inst[x]->sounds[y]->wavSecondary.base = CharArrayToLong(&ctl[offsetWaveTableSecondary + 0x4]);
						alBank->inst[x]->sounds[y]->wavSecondary.len = CharArrayToLong(&ctl[offsetWaveTableSecondary + 0x0]) & 0xFFFFFF;

						alBank->inst[x]->sounds[y]->wavSecondary.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wavSecondary.len];

						if (ctl[offsetWaveTableSecondary] == 0x30)
						{
							//30 special somehow
							alBank->inst[x]->sounds[y]->wavSecondary.decode8Only = true;
						}

						for (int  r = 0; r < alBank->inst[x]->sounds[y]->wavSecondary.len; r++)
						{
							alBank->inst[x]->sounds[y]->wavSecondary.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wavSecondary.base + r];
						}
						
						alBank->inst[x]->sounds[y]->wavSecondary.type = AL_ADPCM_WAVE;
						alBank->inst[x]->sounds[y]->wavSecondary.flags = 0;
						// MUST PAD to 4s

						if ((alBank->inst[x]->sounds[y]->wavSecondary.type == AL_ADPCM_WAVE) && ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1)))
						{
							alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave = new ALADPCMWaveInfo();
							unsigned long loopOffsetSecondary = CharArrayToLong(&ctl[offsetWaveTableSecondary + 0x8]);
							unsigned long predictorOffsetSecondary = CharArrayToLong(&ctl[offsetWaveTableSecondary + 0xC]);

							if (loopOffsetSecondary != 0)
							{
								loopOffsetSecondary = ctlOffset + loopOffsetSecondary;

								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop = new ALADPCMloop();
								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffsetSecondary + 0x0]);
								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffsetSecondary + 0x4]);
								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffsetSecondary + 0x8]);
								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop->unknown1 = CharArrayToLong(&ctl[loopOffsetSecondary + 0xC]);

								if (alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop->start != 0)
								{
									for (int z = 0; z < 0x10; z++)
									{
										alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffsetSecondary + 0x10 + z * 2]);
									}
								}
							}
							else
							{
								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop = NULL;
							}

							if (predictorOffsetSecondary != 0)
							{
								predictorOffsetSecondary = ctlOffset + predictorOffsetSecondary;

								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book = new ALADPCMBook();
								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffsetSecondary + 0x0]);
								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffsetSecondary + 0x4]);
								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->npredictors * 8];

								for (int z = 0; z < alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->npredictors * 8; z++)
								{
									alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffsetSecondary + 0x8 + z * 2]);
								}
							}
						}
					}

					unsigned long offsetWaveTablePrevious = CharArrayToLong(&ctl[offsetSoundData+ 0x8]);
					if (offsetWaveTablePrevious == 0x00000000)
						alBank->inst[x]->sounds[y]->hasWavePrevious = false;
					else
					{
						alBank->inst[x]->sounds[y]->hasWavePrevious = true;
						offsetWaveTablePrevious = ctlOffset + offsetWaveTablePrevious;

						alBank->inst[x]->sounds[y]->wavPrevious.base = CharArrayToLong(&ctl[offsetWaveTablePrevious + 0x4]);
						alBank->inst[x]->sounds[y]->wavPrevious.len = CharArrayToLong(&ctl[offsetWaveTablePrevious + 0x0]) & 0xFFFFFF;

						if (ctl[offsetWaveTablePrevious] == 0x30)
						{
							//30 special somehow
							alBank->inst[x]->sounds[y]->wavPrevious.decode8Only = true;
						}
						alBank->inst[x]->sounds[y]->wavPrevious.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wavPrevious.len];

						for (int  r = 0; r < alBank->inst[x]->sounds[y]->wavPrevious.len; r++)
						{
							alBank->inst[x]->sounds[y]->wavPrevious.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wavPrevious.base + r];
						}
						
						alBank->inst[x]->sounds[y]->wavPrevious.type = AL_ADPCM_WAVE;
						alBank->inst[x]->sounds[y]->wavPrevious.flags = 0;
						// MUST PAD to 4s

						if ((alBank->inst[x]->sounds[y]->wavPrevious.type == AL_ADPCM_WAVE) && ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1)))
						{
							alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave = new ALADPCMWaveInfo();
							unsigned long loopOffsetPrevious = CharArrayToLong(&ctl[offsetWaveTablePrevious + 0x8]);
							unsigned long predictorOffsetPrevious = CharArrayToLong(&ctl[offsetWaveTablePrevious + 0xC]);

							if (loopOffsetPrevious != 0)
							{
								loopOffsetPrevious = ctlOffset + loopOffsetPrevious;

								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop = new ALADPCMloop();
								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffsetPrevious + 0x0]);
								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffsetPrevious + 0x4]);
								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffsetPrevious + 0x8]);
								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop->unknown1 = CharArrayToLong(&ctl[loopOffsetPrevious + 0xC]);

								if (alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop->start != 0)
								{
									for (int z = 0; z < 0x10; z++)
									{
										alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffsetPrevious + 0x10 + z * 2]);
									}
								}
							}
							else
							{
								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop = NULL;
							}

							if (predictorOffsetPrevious != 0)
							{
								predictorOffsetPrevious = ctlOffset + predictorOffsetPrevious;

								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book = new ALADPCMBook();
								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffsetPrevious + 0x0]);
								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffsetPrevious + 0x4]);
								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->npredictors * 8];

								for (int z = 0; z < alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->npredictors * 8; z++)
								{
									alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffsetPrevious + 0x8 + z * 2]);
								}
							}
						}
					}

					/*float keyBasePrev = *reinterpret_cast<float*> (&alBank->inst[x]->sounds[y]->floatKeyBasePrev);
					float floatKeyBase = *reinterpret_cast<float*> (&alBank->inst[x]->sounds[y]->floatKeyBase);
					float floatKeyBaseSec = *reinterpret_cast<float*> (&alBank->inst[x]->sounds[y]->floatKeyBaseSec);

					unsigned char keyBasePrevKey = ConvertEADGameValueToKeyBase(keyBasePrev);
					unsigned char floatKeyBaseKey = ConvertEADGameValueToKeyBase(floatKeyBase);
					unsigned char floatKeyBaseSecKey = ConvertEADGameValueToKeyBase(floatKeyBaseSec);

					FILE* outA = fopen("C:\\temp\\keyparse.txt", "a");
					if (alBank->inst[x]->sounds[y]->hasWavePrevious && alBank->inst[x]->sounds[y]->hasWaveSecondary)
						fprintf(outA, "Inst:%02X Prev %02X Prim %02X Sec  %02X   (%08X)", x, keyBasePrevKey, floatKeyBaseKey, floatKeyBaseSecKey, alBank->inst[x]->sounds[y]->unknown1);
					else if (alBank->inst[x]->sounds[y]->hasWavePrevious)
						fprintf(outA, "Inst:%02X Prev %02X Prim %02X           (%08X)", x, keyBasePrevKey, floatKeyBaseKey, alBank->inst[x]->sounds[y]->unknown1);
					else if (alBank->inst[x]->sounds[y]->hasWaveSecondary)
						fprintf(outA, "Inst:%02X         Prim %02X Sec  %02X   (%08X)", x, floatKeyBaseKey, floatKeyBaseSecKey, alBank->inst[x]->sounds[y]->unknown1);
					else
						fprintf(outA, "Inst:%02X         Prim %02X           (%08X)", x, floatKeyBaseKey, alBank->inst[x]->sounds[y]->unknown1);

					if (offsetADRSData != 0)
					{
						fprintf(outA, " ");
						for (int zz = 0; zz < 0x10; zz++)
						{
							fprintf(outA, "%02X", ctl[offsetADRSData+zz]);
							if (((zz % 2) == 1) && (zz > 0))
								fprintf(outA, " ");
						}
					}

					fprintf(outA, "\n");
					fclose(outA);*/
				}
			}
			else if (x < (instrumentCountNormal + instrumentCountSection1))
			{
				int percussionInNumber = x - instrumentCountNormal;

				alBank->eadPercussion[percussionInNumber].wav.type = AL_ADPCM_WAVE;

				unsigned long percussionItemOffset = CharArrayToLong(&ctl[ctlOffset + offsetInstrumentSection1 + (x-instrumentCountNormal)*4]);
				if (percussionItemOffset == 0x0000)
				{
					continue;
				}

				percussionItemOffset = ctlOffset + percussionItemOffset;

				unsigned long offsetWaveTable = ctlOffset + CharArrayToLong(&ctl[percussionItemOffset+0x4]);

				alBank->eadPercussion[percussionInNumber].unknown1A = ctl[percussionItemOffset+0x0];
				alBank->eadPercussion[percussionInNumber].pan = ctl[percussionItemOffset+0x1];
				alBank->eadPercussion[percussionInNumber].unknown1C = CharArrayToShort(&ctl[percussionItemOffset+0x2]);

				alBank->eadPercussion[percussionInNumber].keyBase = CharArrayToLong(&ctl[percussionItemOffset+0x8]);

				unsigned long offsetADRSData = CharArrayToLong(&ctl[percussionItemOffset + 0xC]);
				if (offsetADRSData != 0)
				{
					offsetADRSData = ctlOffset + offsetADRSData;

					for (int z = 0; z < 8; z++)
					{
						alBank->eadPercussion[percussionInNumber].adsrEAD[z] = CharArrayToShort(&ctl[offsetADRSData + z*2]);
					}
				}

				alBank->eadPercussion[percussionInNumber].wav.unknown1 = CharArrayToLong(&ctl[offsetWaveTable + 0x10]);
				alBank->eadPercussion[percussionInNumber].wav.base = CharArrayToLong(&ctl[offsetWaveTable + 0x4]);
				alBank->eadPercussion[percussionInNumber].wav.len = CharArrayToLong(&ctl[offsetWaveTable + 0x0]) & 0xFFFFFF;
				alBank->eadPercussion[percussionInNumber].wav.unknown2 = CharArrayToLong(&ctl[offsetWaveTable + 0x14]);
				alBank->eadPercussion[percussionInNumber].wav.unknown3 = CharArrayToLong(&ctl[offsetWaveTable + 0x18]);
				alBank->eadPercussion[percussionInNumber].wav.unknown4 = CharArrayToLong(&ctl[offsetWaveTable + 0x1C]);

				if (ctl[ctlOffset] == 0x30)
				{
					// special but not sure what
					alBank->eadPercussion[percussionInNumber].wav.decode8Only = true;
				}

				alBank->eadPercussion[percussionInNumber].wav.wavData = new unsigned char[alBank->eadPercussion[percussionInNumber].wav.len];

				for (int  r = 0; r < alBank->eadPercussion[percussionInNumber].wav.len; r++)
				{
					alBank->eadPercussion[percussionInNumber].wav.wavData[r] = tbl[alBank->eadPercussion[percussionInNumber].wav.base + r];
				}

				alBank->eadPercussion[percussionInNumber].wav.type = AL_ADPCM_WAVE;
				alBank->eadPercussion[percussionInNumber].wav.flags = 0;

				alBank->eadPercussion[percussionInNumber].wav.adpcmWave = new ALADPCMWaveInfo();
				unsigned long loopOffset;
				unsigned long predictorOffset;
				
				loopOffset = CharArrayToLong(&ctl[offsetWaveTable + 0x8]);
				predictorOffset = CharArrayToLong(&ctl[offsetWaveTable + 0xC]);

				if (loopOffset != 0)
				{
					loopOffset = ctlOffset + loopOffset;

					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->loop = new ALADPCMloop();
					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);
					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->loop->unknown1 = CharArrayToLong(&ctl[loopOffset + 0xC]);

					if (alBank->eadPercussion[percussionInNumber].wav.adpcmWave->loop->start != 0)
					{
						for (int z = 0; z < 0x10; z++)
						{
							alBank->eadPercussion[percussionInNumber].wav.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffset + 0x10 + z * 2]);
						}
					}
				}
				else
				{
					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->loop = NULL;
				}

				if (predictorOffset != 0)
				{
					predictorOffset = ctlOffset + predictorOffset;

					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book = new ALADPCMBook();
					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffset + 0x0]);
					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffset + 0x4]);
					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book->predictors = new signed short[alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book->order * alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book->npredictors * 8];

					for (int z = 0; z < alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book->order * alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book->npredictors * 8; z++)
					{
						alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + 0x8 + z * 2]);
					}
				}
				else
				{
					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book = NULL;
				}
				continue;
			}
			else if (x < (instrumentCountNormal + instrumentCountSection1 + instrumentCountSection2))
			{
				int soundInNumber = x - instrumentCountNormal - instrumentCountSection1;

				unsigned long offsetInstrument = CharArrayToLong(&ctl[ctlOffset + offsetInstrumentSection2 + (x-instrumentCountNormal-instrumentCountSection1)*8]);
				if (offsetInstrument == 0x0000)
				{
					alBank->alSfx[soundInNumber] = NULL;
					continue;
				}

				offsetInstrument = ctlOffset + offsetInstrument;

				unsigned long offsetSound = offsetInstrument;


				alBank->alSfx[soundInNumber] = new ALWave();

				alBank->alSfx[soundInNumber]->wavData = NULL;

				alBank->alSfx[soundInNumber]->base = CharArrayToLong(&ctl[offsetSound + 0x4]);
				alBank->alSfx[soundInNumber]->len = CharArrayToLong(&ctl[offsetSound + 0x0]) & 0xFFFFFF;
				alBank->alSfx[soundInNumber]->wavData = new unsigned char[alBank->alSfx[soundInNumber]->len];

				if (ctl[offsetSound] == 0x30)
				{
					// special but not sure what
					alBank->alSfx[soundInNumber]->decode8Only = true;
				}
				for (int  r = 0; r < alBank->alSfx[soundInNumber]->len; r++)
				{
					alBank->alSfx[soundInNumber]->wavData[r] = tbl[alBank->alSfx[soundInNumber]->base + r];
				}
				
				alBank->alSfx[soundInNumber]->type == AL_ADPCM_WAVE;
				alBank->alSfx[soundInNumber]->flags = 0x00;

				alBank->alSfx[soundInNumber]->adpcmWave = new ALADPCMWaveInfo();

				unsigned long predictorOffset = CharArrayToLong(&ctl[offsetSound + 0xC]);
				if (predictorOffset != 0)
				{
					if (alBank->alSfx[soundInNumber]->flags == 0x1)
						predictorOffset = predictorOffset & 0xFFFFFF;
					else
						predictorOffset = ctlOffset + predictorOffset;

					alBank->alSfx[soundInNumber]->adpcmWave->loop = NULL;

					alBank->alSfx[soundInNumber]->adpcmWave->book = new ALADPCMBook();
					alBank->alSfx[soundInNumber]->adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffset + 0x0]);
					alBank->alSfx[soundInNumber]->adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffset + 0x4]);
					alBank->alSfx[soundInNumber]->adpcmWave->book->predictors = new signed short[alBank->alSfx[soundInNumber]->adpcmWave->book->order * alBank->alSfx[soundInNumber]->adpcmWave->book->npredictors * 8];

					for (int z = 0; z < alBank->alSfx[soundInNumber]->adpcmWave->book->order * alBank->alSfx[soundInNumber]->adpcmWave->book->npredictors * 8; z++)
					{
						alBank->alSfx[soundInNumber]->adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + 0x8 + z * 2]);
					}
				}

				unsigned long loopOffset = CharArrayToLong(&ctl[offsetSound + 0x8]);
				if (loopOffset != 0)
				{
					if (alBank->alSfx[soundInNumber]->flags == 0x1)
						loopOffset = loopOffset & 0xFFFFFF;
					else
						loopOffset = ctlOffset + loopOffset;

					alBank->alSfx[soundInNumber]->adpcmWave->loop = new ALADPCMloop();
					alBank->alSfx[soundInNumber]->adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
					alBank->alSfx[soundInNumber]->adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
					alBank->alSfx[soundInNumber]->adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);
					for (int z = 0; z < 0x10; z++)
					{
						alBank->alSfx[soundInNumber]->adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffset + 0xC + z * 2]);
					}
				}
				else
				{
					alBank->alSfx[soundInNumber]->adpcmWave->loop = NULL;
				}
				continue;
			}
		}
	}

	return alBank;
}


ALBank* CN64AIFCAudio::ReadAudioStarFox(unsigned char* ctl, int ctlSize, int ctlOffset, unsigned char* tbl, int instrumentCount, unsigned long endSpot)
{
	ALBank* alBank = new ALBank();
	alBank->soundBankFormat = STARFOX64FORMAT;
	alBank->count = instrumentCount;
	alBank->flags = 0x0000;
	alBank->pad = 0x0000;
	alBank->samplerate = 8000;
	alBank->percussion = 0x0000;

	unsigned short numberBands = 1;
	unsigned long bankOffset = 0;

	int instrumentCountNormal = instrumentCount;
	int instrumentCountSection1 = 0;

	unsigned long offsetInstrumentSection1 = CharArrayToLong(&ctl[ctlOffset]);
	unsigned long endOffsetInstrument1Section1 = 0;

	alBank->eadPercussion = NULL;

	if (offsetInstrumentSection1 != NULL)
	{
		endOffsetInstrument1Section1 = endSpot - ctlOffset;
		instrumentCountSection1 = ((endOffsetInstrument1Section1 - offsetInstrumentSection1) / 4);

		alBank->eadPercussion = new EADPercussion[instrumentCountSection1];
	}

	alBank->inst = NULL;
	alBank->countEADPercussion = instrumentCountSection1;
	

	if ((alBank->flags == 0x0000) || (alBank->flags == 0x0100)) // offset
	{
		alBank->inst = new ALInst*[alBank->count];

		for (int x = 0; x < alBank->count; x++)
		{
			alBank->inst[x] = new ALInst();
			alBank->inst[x]->samplerate = 0;
			alBank->inst[x]->sounds = NULL;
		}

		for (int x = 0; x < alBank->count + alBank->countEADPercussion; x++)
		{		
			if (x < instrumentCountNormal)
			{
				unsigned long offsetInstrument = CharArrayToLong(&ctl[ctlOffset + x*4 + 0x4]);
				if (offsetInstrument == 0x0000)
				{
					alBank->inst[x]->soundCount = 0;
					alBank->inst[x]->sounds = NULL;
					continue;
				}
				offsetInstrument = ctlOffset + offsetInstrument;
				
				alBank->inst[x]->soundCount = 1;

				alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

				for (int y = 0; y < alBank->inst[x]->soundCount; y++)
				{
					alBank->inst[x]->sounds[y] = new ALSound();
					alBank->inst[x]->sounds[y]->wav.wavData = NULL;
				}

				for (int y = 0; y < alBank->inst[x]->soundCount; y++)
				{
					unsigned long offsetSoundData = offsetInstrument;

					alBank->inst[x]->sounds[y]->unknown1 = CharArrayToLong(&ctl[offsetInstrument + 0x0]);
					alBank->inst[x]->sounds[y]->floatKeyBasePrev = CharArrayToLong(&ctl[offsetInstrument + 0xC]);
					alBank->inst[x]->sounds[y]->floatKeyBase = CharArrayToLong(&ctl[offsetInstrument + 0x14]);
					alBank->inst[x]->sounds[y]->floatKeyBaseSec = CharArrayToLong(&ctl[offsetInstrument + 0x1C]);
					unsigned long offsetADRSData = CharArrayToLong(&ctl[offsetInstrument + 0x4]);
					if (offsetADRSData != 0)
					{
						offsetADRSData = ctlOffset + offsetADRSData;

						for (int z = 0; z < 8; z++)
						{
							alBank->inst[x]->sounds[y]->adsrEAD[z] = CharArrayToShort(&ctl[offsetADRSData + z*2]);
						}
					}


					unsigned long offsetWaveTable = CharArrayToLong(&ctl[offsetSoundData+ 0x10]);
					offsetWaveTable = ctlOffset + offsetWaveTable;

					alBank->inst[x]->sounds[y]->wav.base = CharArrayToLong(&ctl[offsetWaveTable + 0x4]);
					alBank->inst[x]->sounds[y]->wav.len = CharArrayToLong(&ctl[offsetWaveTable + 0x0]) & 0xFFFFFF;

					alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];

					for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
					{
						alBank->inst[x]->sounds[y]->wav.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wav.base + r];
					}
					
					alBank->inst[x]->sounds[y]->wav.type = AL_ADPCM_WAVE;
					alBank->inst[x]->sounds[y]->wav.flags = 0;
					// MUST PAD to 4s

					if ((alBank->inst[x]->sounds[y]->wav.type == AL_ADPCM_WAVE) && ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1)))
					{
						alBank->inst[x]->sounds[y]->wav.adpcmWave = new ALADPCMWaveInfo();
						unsigned long loopOffset = CharArrayToLong(&ctl[offsetWaveTable + 0x8]);
						unsigned long predictorOffset = CharArrayToLong(&ctl[offsetWaveTable + 0xC]);

						if (loopOffset != 0)
						{
							loopOffset = ctlOffset + loopOffset;

							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = new ALADPCMloop();
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->unknown1 = CharArrayToLong(&ctl[loopOffset + 0xC]);

							if (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start != 0)
							{
								for (int z = 0; z < 0x10; z++)
								{
									alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffset + 0x10 + z * 2]);
								}
							}
						}
						else
						{
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = NULL;
						}

						if (predictorOffset != 0)
						{
							predictorOffset = ctlOffset + predictorOffset;

							alBank->inst[x]->sounds[y]->wav.adpcmWave->book = new ALADPCMBook();
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffset + 0x0]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffset + 0x4]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8];

							for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8; z++)
							{
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + 0x8 + z * 2]);
							}
						}
					}


					unsigned long offsetWaveTableSecondary = CharArrayToLong(&ctl[offsetSoundData+ 0x18]);
					if (offsetWaveTableSecondary == 0x00000000)
						alBank->inst[x]->sounds[y]->hasWaveSecondary = false;
					else
					{
						alBank->inst[x]->sounds[y]->hasWaveSecondary = true;
						offsetWaveTableSecondary = ctlOffset + offsetWaveTableSecondary;

						alBank->inst[x]->sounds[y]->wavSecondary.base = CharArrayToLong(&ctl[offsetWaveTableSecondary + 0x4]);
						alBank->inst[x]->sounds[y]->wavSecondary.len = CharArrayToLong(&ctl[offsetWaveTableSecondary + 0x0]) & 0xFFFFFF;

						alBank->inst[x]->sounds[y]->wavSecondary.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wavSecondary.len];

						for (int  r = 0; r < alBank->inst[x]->sounds[y]->wavSecondary.len; r++)
						{
							alBank->inst[x]->sounds[y]->wavSecondary.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wavSecondary.base + r];
						}
						
						alBank->inst[x]->sounds[y]->wavSecondary.type = AL_ADPCM_WAVE;
						alBank->inst[x]->sounds[y]->wavSecondary.flags = 0;
						// MUST PAD to 4s

						if ((alBank->inst[x]->sounds[y]->wavSecondary.type == AL_ADPCM_WAVE) && ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1)))
						{
							alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave = new ALADPCMWaveInfo();
							unsigned long loopOffsetSecondary = CharArrayToLong(&ctl[offsetWaveTableSecondary + 0x8]);
							unsigned long predictorOffsetSecondary = CharArrayToLong(&ctl[offsetWaveTableSecondary + 0xC]);

							if (loopOffsetSecondary != 0)
							{
								loopOffsetSecondary = ctlOffset + loopOffsetSecondary;

								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop = new ALADPCMloop();
								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffsetSecondary + 0x0]);
								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffsetSecondary + 0x4]);
								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffsetSecondary + 0x8]);
								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop->unknown1 = CharArrayToLong(&ctl[loopOffsetSecondary + 0xC]);

								if (alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop->start != 0)
								{
									for (int z = 0; z < 0x10; z++)
									{
										alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffsetSecondary + 0x10 + z * 2]);
									}
								}
							}
							else
							{
								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop = NULL;
							}

							if (predictorOffsetSecondary != 0)
							{
								predictorOffsetSecondary = ctlOffset + predictorOffsetSecondary;

								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book = new ALADPCMBook();
								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffsetSecondary + 0x0]);
								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffsetSecondary + 0x4]);
								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->npredictors * 8];

								for (int z = 0; z < alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->npredictors * 8; z++)
								{
									alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffsetSecondary + 0x8 + z * 2]);
								}
							}
						}
					}

					unsigned long offsetWaveTablePrevious = CharArrayToLong(&ctl[offsetSoundData+ 0x8]);
					if (offsetWaveTablePrevious == 0x00000000)
						alBank->inst[x]->sounds[y]->hasWavePrevious = false;
					else
					{
						alBank->inst[x]->sounds[y]->hasWavePrevious = true;
						offsetWaveTablePrevious = ctlOffset + offsetWaveTablePrevious;

						alBank->inst[x]->sounds[y]->wavPrevious.base = CharArrayToLong(&ctl[offsetWaveTablePrevious + 0x4]);
						alBank->inst[x]->sounds[y]->wavPrevious.len = CharArrayToLong(&ctl[offsetWaveTablePrevious + 0x0]) & 0xFFFFFF;

						alBank->inst[x]->sounds[y]->wavPrevious.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wavPrevious.len];

						for (int  r = 0; r < alBank->inst[x]->sounds[y]->wavPrevious.len; r++)
						{
							alBank->inst[x]->sounds[y]->wavPrevious.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wavPrevious.base + r];
						}
						
						alBank->inst[x]->sounds[y]->wavPrevious.type = AL_ADPCM_WAVE;
						alBank->inst[x]->sounds[y]->wavPrevious.flags = 0;
						// MUST PAD to 4s

						if ((alBank->inst[x]->sounds[y]->wavPrevious.type == AL_ADPCM_WAVE) && ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1)))
						{
							alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave = new ALADPCMWaveInfo();
							unsigned long loopOffsetPrevious = CharArrayToLong(&ctl[offsetWaveTablePrevious + 0x8]);
							unsigned long predictorOffsetPrevious = CharArrayToLong(&ctl[offsetWaveTablePrevious + 0xC]);

							if (loopOffsetPrevious != 0)
							{
								loopOffsetPrevious = ctlOffset + loopOffsetPrevious;

								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop = new ALADPCMloop();
								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffsetPrevious + 0x0]);
								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffsetPrevious + 0x4]);
								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffsetPrevious + 0x8]);
								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop->unknown1 = CharArrayToLong(&ctl[loopOffsetPrevious + 0xC]);

								if (alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop->start != 0)
								{
									for (int z = 0; z < 0x10; z++)
									{
										alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffsetPrevious + 0x10 + z * 2]);
									}
								}
							}
							else
							{
								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop = NULL;
							}

							if (predictorOffsetPrevious != 0)
							{
								predictorOffsetPrevious = ctlOffset + predictorOffsetPrevious;

								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book = new ALADPCMBook();
								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffsetPrevious + 0x0]);
								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffsetPrevious + 0x4]);
								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->npredictors * 8];

								for (int z = 0; z < alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->npredictors * 8; z++)
								{
									alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffsetPrevious + 0x8 + z * 2]);
								}
							}
						}
					}
				}
			}
			else if (x < (instrumentCountNormal + instrumentCountSection1))
			{
				int percussionInNumber = x - instrumentCountNormal;

				unsigned long percussionItemOffset = CharArrayToLong(&ctl[ctlOffset + offsetInstrumentSection1 + (x-instrumentCountNormal)*4]);
				if (percussionItemOffset == 0x0000)
				{
					continue;
				}
				percussionItemOffset = ctlOffset + percussionItemOffset;

				unsigned long offsetWaveTable = ctlOffset + CharArrayToLong(&ctl[percussionItemOffset+0x4]);

				alBank->eadPercussion[percussionInNumber].unknown1A = ctl[percussionItemOffset+0x0];
				alBank->eadPercussion[percussionInNumber].pan = ctl[percussionItemOffset+0x1];
				alBank->eadPercussion[percussionInNumber].unknown1C = CharArrayToShort(&ctl[percussionItemOffset+0x2]);

				alBank->eadPercussion[percussionInNumber].keyBase = CharArrayToLong(&ctl[percussionItemOffset+0x8]);

				unsigned long offsetADRSData = CharArrayToLong(&ctl[percussionItemOffset + 0xC]);
				if (offsetADRSData != 0)
				{
					offsetADRSData = ctlOffset + offsetADRSData;

					for (int z = 0; z < 8; z++)
					{
						alBank->eadPercussion[percussionInNumber].adsrEAD[z] = CharArrayToShort(&ctl[offsetADRSData + z*2]);
					}
				}

				alBank->eadPercussion[percussionInNumber].wav.unknown1 = CharArrayToLong(&ctl[offsetWaveTable + 0x10]);
				alBank->eadPercussion[percussionInNumber].wav.base = CharArrayToLong(&ctl[offsetWaveTable + 0x4]);
				alBank->eadPercussion[percussionInNumber].wav.len = CharArrayToLong(&ctl[offsetWaveTable + 0x0]) & 0xFFFFFF;
				alBank->eadPercussion[percussionInNumber].wav.unknown2 = CharArrayToLong(&ctl[offsetWaveTable + 0x14]);
				alBank->eadPercussion[percussionInNumber].wav.unknown3 = CharArrayToLong(&ctl[offsetWaveTable + 0x18]);
				alBank->eadPercussion[percussionInNumber].wav.unknown4 = CharArrayToLong(&ctl[offsetWaveTable + 0x1C]);

				alBank->eadPercussion[percussionInNumber].wav.wavData = new unsigned char[alBank->eadPercussion[percussionInNumber].wav.len];

				for (int  r = 0; r < alBank->eadPercussion[percussionInNumber].wav.len; r++)
				{
					alBank->eadPercussion[percussionInNumber].wav.wavData[r] = tbl[alBank->eadPercussion[percussionInNumber].wav.base + r];
				}

				alBank->eadPercussion[percussionInNumber].wav.type = AL_ADPCM_WAVE;
				alBank->eadPercussion[percussionInNumber].wav.flags = 0;

				alBank->eadPercussion[percussionInNumber].wav.adpcmWave = new ALADPCMWaveInfo();
				unsigned long loopOffset;
				unsigned long predictorOffset;
				
				loopOffset = CharArrayToLong(&ctl[offsetWaveTable + 0x8]);
				predictorOffset = CharArrayToLong(&ctl[offsetWaveTable + 0xC]);

				if (loopOffset != 0)
				{
					loopOffset = ctlOffset + loopOffset;

					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->loop = new ALADPCMloop();
					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);
					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->loop->unknown1 = CharArrayToLong(&ctl[loopOffset + 0xC]);

					if (alBank->eadPercussion[percussionInNumber].wav.adpcmWave->loop->start != 0)
					{
						for (int z = 0; z < 0x10; z++)
						{
							alBank->eadPercussion[percussionInNumber].wav.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffset + 0x10 + z * 2]);
						}
					}
				}
				else
				{
					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->loop = NULL;
				}

				if (predictorOffset != 0)
				{
					predictorOffset = ctlOffset + predictorOffset;

					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book = new ALADPCMBook();
					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffset + 0x0]);
					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffset + 0x4]);
					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book->predictors = new signed short[alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book->order * alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book->npredictors * 8];

					for (int z = 0; z < alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book->order * alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book->npredictors * 8; z++)
					{
						alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + 0x8 + z * 2]);
					}
				}
				else
				{
					alBank->eadPercussion[percussionInNumber].wav.adpcmWave->book = NULL;
				}
				continue;
			}
		}
	}

	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioMario(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl, unsigned long& tblSize, int bankNumber)
{
	return ReadAudioMario(ctl, ctlSize, ctlOffset, tbl, tblSize, false, bankNumber);
}

ALBank* CN64AIFCAudio::ReadAudioMario(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl, unsigned long& tblSize, bool marioKartStyle, int bankNumber)
{
	FILE* outDebug = NULL;
	//FILE* outDebug = fopen("C:\\temp\\mariodata.txt", "w");;

	ALBank* alBank = new ALBank();
	if (marioKartStyle)
		alBank->soundBankFormat = MARIOKART64FORMAT;
	else
		alBank->soundBankFormat = SUPERMARIO64FORMAT;

	//int bankCount = CharArrayToShort(&ctl[ctlOffset+2]);

	alBank->flags = 0x0000;
	alBank->samplerate = 22050;

	alBank->inst = NULL;

	if ((alBank->flags == 0x0000) || (alBank->flags == 0x0100)) // offset
	{
		unsigned long offsetInstrument = ctlOffset + CharArrayToLong(&ctl[ctlOffset + 4 + (bankNumber * 8)]);
		unsigned long offsetTbl = CharArrayToLong(&tbl[4 + (bankNumber * 8)]);

		alBank->count = CharArrayToLong(&ctl[offsetInstrument]);
		alBank->inst = new ALInst*[alBank->count];

		alBank->countEADPercussion = CharArrayToLong(&ctl[offsetInstrument+4]);
		alBank->eadPercussion = NULL;

		for (int x = 0; x < alBank->count; x++)
		{
			alBank->inst[x] = new ALInst();
			alBank->inst[x]->samplerate = 0;
			alBank->inst[x]->sounds = NULL;
		}

		alBank->unknown2 = CharArrayToLong(&ctl[offsetInstrument+8]);
		alBank->unknown3 = CharArrayToLong(&ctl[offsetInstrument+0xC]);

		unsigned long offsetSoundData = offsetInstrument + 0x10;

		for (int x = 0; x < alBank->count; x++)
		{
			alBank->inst[x]->soundCount = 0;

			if ((alBank->inst[x]->flags == 0x0) || (alBank->inst[x]->flags == 0x1))
			{
				int y = 0;

				alBank->inst[x]->soundCount = 1;

				alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

				for (int y = 0; y < alBank->inst[x]->soundCount; y++)
				{
					alBank->inst[x]->sounds[y] = new ALSound();
					alBank->inst[x]->sounds[y]->wav.wavData = NULL;
				}

				unsigned long offsetSound = CharArrayToLong(&ctl[offsetSoundData + 4 + x*0x4]);
				if (offsetSound == 0x0)
				{
					delete [] alBank->inst[x]->sounds[y];
					alBank->inst[x]->sounds[y] = NULL;
					alBank->inst[x]->soundCount = 0;
					continue;
				}

				offsetSound = offsetSoundData + offsetSound;

				alBank->inst[x]->sounds[y]->flags = 0x0;

				alBank->inst[x]->sounds[y]->unknown1 = CharArrayToLong(&ctl[offsetSound+ 0x0]);
				alBank->inst[x]->sounds[y]->floatKeyBasePrev = CharArrayToLong(&ctl[offsetSound+ 0xC]);
				alBank->inst[x]->sounds[y]->floatKeyBase = CharArrayToLong(&ctl[offsetSound+ 0x14]);
				alBank->inst[x]->sounds[y]->floatKeyBaseSec = CharArrayToLong(&ctl[offsetSound+ 0x1C]);
				unsigned long offsetADRSData = CharArrayToLong(&ctl[offsetSound + 0x4]);
				if (offsetADRSData != 0)
				{
					offsetADRSData = offsetInstrument + offsetADRSData + 0x10;

					for (int z = 0; z < 8; z++)
					{
						alBank->inst[x]->sounds[y]->adsrEAD[z] = CharArrayToShort(&ctl[offsetADRSData + z*2]);
					}
				}

				unsigned long offsetWaveTable = CharArrayToLong(&ctl[offsetSound+ 0x10]);
				offsetWaveTable = offsetSoundData + offsetWaveTable;

				alBank->inst[x]->sounds[y]->wav.unknown1 = CharArrayToLong(&ctl[offsetWaveTable + 0x0]);
				alBank->inst[x]->sounds[y]->wav.base = CharArrayToLong(&ctl[offsetWaveTable + 0x4]);
				alBank->inst[x]->sounds[y]->wav.len = CharArrayToLong(&ctl[offsetWaveTable + 0x10]);
				alBank->inst[x]->sounds[y]->wav.unknown2 = CharArrayToLong(&ctl[offsetWaveTable + 0x14]);
				alBank->inst[x]->sounds[y]->wav.unknown3 = CharArrayToLong(&ctl[offsetWaveTable + 0x18]);
				alBank->inst[x]->sounds[y]->wav.unknown4 = CharArrayToLong(&ctl[offsetWaveTable + 0x1C]);

				alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];

				for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
				{
					alBank->inst[x]->sounds[y]->wav.wavData[r] = tbl[offsetTbl + alBank->inst[x]->sounds[y]->wav.base + r];
				}

				if (outDebug != NULL)
				{
					fprintf(outDebug, "Instrument %02X Sound %02X Length %08X ", x, y, alBank->inst[x]->sounds[y]->wav.len);
					for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
					{
						fprintf(outDebug, "%02X", alBank->inst[x]->sounds[y]->wav.wavData[r]);
					}
					fprintf(outDebug, "\n");
				}
				
				alBank->inst[x]->sounds[y]->wav.type = AL_ADPCM_WAVE;
				alBank->inst[x]->sounds[y]->wav.flags = 0;
				// MUST PAD to 4s

				if ((alBank->inst[x]->sounds[y]->wav.type == AL_ADPCM_WAVE) && ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1)))
				{
					alBank->inst[x]->sounds[y]->wav.adpcmWave = new ALADPCMWaveInfo();
					unsigned long loopOffset = CharArrayToLong(&ctl[offsetWaveTable + 0x8]);
					unsigned long predictorOffset = CharArrayToLong(&ctl[offsetWaveTable + 0xC]);

					if (loopOffset != 0)
					{
						loopOffset = offsetSoundData + loopOffset;

						alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = new ALADPCMloop();
						alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
						alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
						alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);
						alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->unknown1 = CharArrayToLong(&ctl[loopOffset + 0xC]);

						if (alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start != 0)
						{
							for (int z = 0; z < 0x10; z++)
							{
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffset + 0x10 + z * 2]);
							}
						}
					}
					else
					{
						alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = NULL;
					}

					if (predictorOffset != 0)
					{
						predictorOffset = offsetSoundData + predictorOffset;

						alBank->inst[x]->sounds[y]->wav.adpcmWave->book = new ALADPCMBook();
						alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffset + 0x0]);
						alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffset + 0x4]);
						alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8];

						for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8; z++)
						{
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + 0x8 + z * 2]);
						}
					}
				}


				unsigned long offsetWaveTableSecondary = CharArrayToLong(&ctl[offsetSound+ 0x18]);
				if (offsetWaveTableSecondary == 0x00000000)
					alBank->inst[x]->sounds[y]->hasWaveSecondary = false;
				else
				{
					alBank->inst[x]->sounds[y]->hasWaveSecondary = true;
					offsetWaveTableSecondary = offsetSoundData + offsetWaveTableSecondary;

					alBank->inst[x]->sounds[y]->wavSecondary.unknown1 = CharArrayToLong(&ctl[offsetWaveTableSecondary + 0x0]);
					alBank->inst[x]->sounds[y]->wavSecondary.base = CharArrayToLong(&ctl[offsetWaveTableSecondary + 0x4]);
					alBank->inst[x]->sounds[y]->wavSecondary.len = CharArrayToLong(&ctl[offsetWaveTableSecondary + 0x10]);
					alBank->inst[x]->sounds[y]->wavSecondary.unknown2 = CharArrayToLong(&ctl[offsetWaveTableSecondary + 0x14]);
					alBank->inst[x]->sounds[y]->wavSecondary.unknown3 = CharArrayToLong(&ctl[offsetWaveTableSecondary + 0x18]);
					alBank->inst[x]->sounds[y]->wavSecondary.unknown4 = CharArrayToLong(&ctl[offsetWaveTableSecondary + 0x1C]);

					alBank->inst[x]->sounds[y]->wavSecondary.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wavSecondary.len];

					for (int  r = 0; r < alBank->inst[x]->sounds[y]->wavSecondary.len; r++)
					{
						alBank->inst[x]->sounds[y]->wavSecondary.wavData[r] = tbl[offsetTbl + alBank->inst[x]->sounds[y]->wavSecondary.base + r];
					}

					if (outDebug != NULL)
					{
						fprintf(outDebug, "Instrument %02X Sound Secondary %02X Length %08X ", x, y, alBank->inst[x]->sounds[y]->wavSecondary.len);
						for (int  r = 0; r < alBank->inst[x]->sounds[y]->wavSecondary.len; r++)
						{
							fprintf(outDebug, "%02X", alBank->inst[x]->sounds[y]->wavSecondary.wavData[r]);
						}
						fprintf(outDebug, "\n");
					}
					
					alBank->inst[x]->sounds[y]->wavSecondary.type = AL_ADPCM_WAVE;
					alBank->inst[x]->sounds[y]->wavSecondary.flags = 0;
					// MUST PAD to 4s

					if ((alBank->inst[x]->sounds[y]->wavSecondary.type == AL_ADPCM_WAVE) && ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1)))
					{
						alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave = new ALADPCMWaveInfo();
						unsigned long loopOffsetSecondary = CharArrayToLong(&ctl[offsetWaveTableSecondary + 0x8]);
						unsigned long predictorOffsetSecondary = CharArrayToLong(&ctl[offsetWaveTableSecondary + 0xC]);

						if (loopOffsetSecondary != 0)
						{
							loopOffsetSecondary = offsetSoundData + loopOffsetSecondary;

							alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop = new ALADPCMloop();
							alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffsetSecondary + 0x0]);
							alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffsetSecondary + 0x4]);
							alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffsetSecondary + 0x8]);
							alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop->unknown1 = CharArrayToLong(&ctl[loopOffsetSecondary + 0xC]);

							if (alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop->start != 0)
							{
								for (int z = 0; z < 0x10; z++)
								{
									alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffsetSecondary + 0x10 + z * 2]);
								}
							}
						}
						else
						{
							alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->loop = NULL;
						}

						if (predictorOffsetSecondary != 0)
						{
							predictorOffsetSecondary = offsetSoundData + predictorOffsetSecondary;

							alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book = new ALADPCMBook();
							alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffsetSecondary + 0x0]);
							alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffsetSecondary + 0x4]);
							alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->npredictors * 8];

							for (int z = 0; z < alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->npredictors * 8; z++)
							{
								alBank->inst[x]->sounds[y]->wavSecondary.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffsetSecondary + 0x8 + z * 2]);
							}
						}
					}
				}

				unsigned long offsetWaveTablePrevious = CharArrayToLong(&ctl[offsetSound+ 0x8]);
				if (offsetWaveTablePrevious == 0x00000000)
					alBank->inst[x]->sounds[y]->hasWavePrevious = false;
				else
				{
					alBank->inst[x]->sounds[y]->hasWavePrevious = true;
					offsetWaveTablePrevious = offsetSoundData + offsetWaveTablePrevious;

					alBank->inst[x]->sounds[y]->wavPrevious.unknown1 = CharArrayToLong(&ctl[offsetWaveTablePrevious + 0x0]);
					alBank->inst[x]->sounds[y]->wavPrevious.base = CharArrayToLong(&ctl[offsetWaveTablePrevious + 0x4]);
					alBank->inst[x]->sounds[y]->wavPrevious.len = CharArrayToLong(&ctl[offsetWaveTablePrevious + 0x10]);
					alBank->inst[x]->sounds[y]->wavPrevious.unknown2 = CharArrayToLong(&ctl[offsetWaveTablePrevious + 0x14]);
					alBank->inst[x]->sounds[y]->wavPrevious.unknown3 = CharArrayToLong(&ctl[offsetWaveTablePrevious + 0x18]);
					alBank->inst[x]->sounds[y]->wavPrevious.unknown4 = CharArrayToLong(&ctl[offsetWaveTablePrevious + 0x1C]);

					alBank->inst[x]->sounds[y]->wavPrevious.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wavPrevious.len];

					for (int  r = 0; r < alBank->inst[x]->sounds[y]->wavPrevious.len; r++)
					{
						alBank->inst[x]->sounds[y]->wavPrevious.wavData[r] = tbl[offsetTbl + alBank->inst[x]->sounds[y]->wavPrevious.base + r];
					}

					if (outDebug != NULL)
					{
						fprintf(outDebug, "Instrument %02X Sound Previous %02X Length %08X ", x, y, alBank->inst[x]->sounds[y]->wavPrevious.len);
						for (int  r = 0; r < alBank->inst[x]->sounds[y]->wavPrevious.len; r++)
						{
							fprintf(outDebug, "%02X", alBank->inst[x]->sounds[y]->wavPrevious.wavData[r]);
						}
						fprintf(outDebug, "\n");
					}
					
					alBank->inst[x]->sounds[y]->wavPrevious.type = AL_ADPCM_WAVE;
					alBank->inst[x]->sounds[y]->wavPrevious.flags = 0;
					// MUST PAD to 4s

					if ((alBank->inst[x]->sounds[y]->wavPrevious.type == AL_ADPCM_WAVE) && ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1)))
					{
						alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave = new ALADPCMWaveInfo();
						unsigned long loopOffsetPrevious = CharArrayToLong(&ctl[offsetWaveTablePrevious + 0x8]);
						unsigned long predictorOffsetPrevious = CharArrayToLong(&ctl[offsetWaveTablePrevious + 0xC]);

						if (loopOffsetPrevious != 0)
						{
							loopOffsetPrevious = offsetSoundData + loopOffsetPrevious;

							alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop = new ALADPCMloop();
							alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffsetPrevious + 0x0]);
							alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffsetPrevious + 0x4]);
							alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffsetPrevious + 0x8]);
							alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop->unknown1 = CharArrayToLong(&ctl[loopOffsetPrevious + 0xC]);

							if (alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop->start != 0)
							{
								for (int z = 0; z < 0x10; z++)
								{
									alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffsetPrevious + 0x10 + z * 2]);
								}
							}
						}
						else
						{
							alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->loop = NULL;
						}

						if (predictorOffsetPrevious != 0)
						{
							predictorOffsetPrevious = offsetSoundData + predictorOffsetPrevious;

							alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book = new ALADPCMBook();
							alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffsetPrevious + 0x0]);
							alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffsetPrevious + 0x4]);
							alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->npredictors * 8];

							for (int z = 0; z < alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->npredictors * 8; z++)
							{
								alBank->inst[x]->sounds[y]->wavPrevious.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffsetPrevious + 0x8 + z * 2]);
							}
						}
					}
				}
			}
		}

		if (alBank->countEADPercussion > 0)
		{
			unsigned long percussionOffset = offsetSoundData + CharArrayToLong(&ctl[offsetInstrument+0x10]);
			alBank->eadPercussion = new EADPercussion[alBank->countEADPercussion];

			for (int y = 0; y < alBank->countEADPercussion; y++)
			{
				alBank->eadPercussion[y].wav.type = AL_ADPCM_WAVE;

				unsigned long percussionItemOffset = offsetSoundData + CharArrayToLong(&ctl[percussionOffset+(4*y)]);
				
				unsigned long offsetWaveTable = offsetSoundData + CharArrayToLong(&ctl[percussionItemOffset+0x4]);

				alBank->eadPercussion[y].unknown1A = ctl[percussionItemOffset+0x0];
				alBank->eadPercussion[y].pan = ctl[percussionItemOffset+0x1];
				alBank->eadPercussion[y].unknown1C = CharArrayToShort(&ctl[percussionItemOffset+0x2]);

				alBank->eadPercussion[y].keyBase = CharArrayToLong(&ctl[percussionItemOffset+0x8]);

				unsigned long offsetADRSData = CharArrayToLong(&ctl[percussionItemOffset + 0xC]);
				if (offsetADRSData != 0)
				{
					offsetADRSData = offsetInstrument + offsetADRSData + 0x10;

					for (int z = 0; z < 8; z++)
					{
						alBank->eadPercussion[y].adsrEAD[z] = CharArrayToShort(&ctl[offsetADRSData + z*2]);
					}
				}

				alBank->eadPercussion[y].wav.unknown1 = CharArrayToLong(&ctl[offsetWaveTable + 0x0]);
				alBank->eadPercussion[y].wav.base = CharArrayToLong(&ctl[offsetWaveTable + 0x4]);
				alBank->eadPercussion[y].wav.len = CharArrayToLong(&ctl[offsetWaveTable + 0x10]);
				alBank->eadPercussion[y].wav.unknown2 = CharArrayToLong(&ctl[offsetWaveTable + 0x14]);
				alBank->eadPercussion[y].wav.unknown3 = CharArrayToLong(&ctl[offsetWaveTable + 0x18]);
				alBank->eadPercussion[y].wav.unknown4 = CharArrayToLong(&ctl[offsetWaveTable + 0x1C]);

				alBank->eadPercussion[y].wav.wavData = new unsigned char[alBank->eadPercussion[y].wav.len];

				for (int  r = 0; r < alBank->eadPercussion[y].wav.len; r++)
				{
					alBank->eadPercussion[y].wav.wavData[r] = tbl[offsetTbl + alBank->eadPercussion[y].wav.base + r];
				}

				if (outDebug != NULL)
				{
					fprintf(outDebug, "Percussion %02X Length %08X ", y, alBank->eadPercussion[y].wav.len);
					for (int  r = 0; r < alBank->eadPercussion[y].wav.len; r++)
					{
						fprintf(outDebug, "%02X", alBank->eadPercussion[y].wav.wavData[r]);
					}
					fprintf(outDebug, "\n");
				}
				
				alBank->eadPercussion[y].wav.type = AL_ADPCM_WAVE;
				alBank->eadPercussion[y].wav.flags = 0;

				alBank->eadPercussion[y].wav.adpcmWave = new ALADPCMWaveInfo();
				unsigned long loopOffset;
				unsigned long predictorOffset;
				if (marioKartStyle)
				{
					loopOffset = CharArrayToLong(&ctl[offsetWaveTable + 0x8]);
					predictorOffset = CharArrayToLong(&ctl[offsetWaveTable + 0xC]);

					if ((predictorOffset > 0xF00000) || (loopOffset > 0xF00000))
					{
						loopOffset = 0;
						predictorOffset = 0;
					}
				}
				else
				{
					loopOffset = CharArrayToLong(&ctl[offsetWaveTable + 0x8]);
					predictorOffset = CharArrayToLong(&ctl[offsetWaveTable + 0xC]);
				}

				if (loopOffset != 0)
				{
					loopOffset = offsetSoundData + loopOffset;

					alBank->eadPercussion[y].wav.adpcmWave->loop = new ALADPCMloop();
					alBank->eadPercussion[y].wav.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
					alBank->eadPercussion[y].wav.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
					alBank->eadPercussion[y].wav.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);
					alBank->eadPercussion[y].wav.adpcmWave->loop->unknown1 = CharArrayToLong(&ctl[loopOffset + 0xC]);

					if (alBank->eadPercussion[y].wav.adpcmWave->loop->start != 0)
					{
						for (int z = 0; z < 0x10; z++)
						{
							alBank->eadPercussion[y].wav.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffset + 0x10 + z * 2]);
						}
					}
				}
				else
				{
					alBank->eadPercussion[y].wav.adpcmWave->loop = NULL;
				}

				if (predictorOffset != 0)
				{
					predictorOffset = offsetSoundData + predictorOffset;

					alBank->eadPercussion[y].wav.adpcmWave->book = new ALADPCMBook();
					alBank->eadPercussion[y].wav.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffset + 0x0]);
					alBank->eadPercussion[y].wav.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffset + 0x4]);
					alBank->eadPercussion[y].wav.adpcmWave->book->predictors = new signed short[alBank->eadPercussion[y].wav.adpcmWave->book->order * alBank->eadPercussion[y].wav.adpcmWave->book->npredictors * 8];

					for (int z = 0; z < alBank->eadPercussion[y].wav.adpcmWave->book->order * alBank->eadPercussion[y].wav.adpcmWave->book->npredictors * 8; z++)
					{
						alBank->eadPercussion[y].wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + 0x8 + z * 2]);
					}
				}
				else
				{
					alBank->eadPercussion[y].wav.adpcmWave->book = NULL;
				}
			}
		}
		else
		{
			alBank->eadPercussion = NULL;
		}
	}

	if (outDebug != NULL)
	{
		fflush(outDebug);
		fclose(outDebug);
	}

	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioRawAllowed(unsigned char* ROM, unsigned char* ctl, int ctlSize, int ctlOffset, unsigned char* tbl, int ctlFlaggedOffset, unsigned long mask, int bankNumber)
{
	ALBank* alBank = ReadAudio(ROM, ctl, ctlSize, ctlOffset, tbl, ctlFlaggedOffset, mask, bankNumber);
	alBank->soundBankFormat = STANDARDFORMATRAWALLOWED;
	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioN64PtrWavetableV2ZLIB(unsigned char* ctl, unsigned long& ctlSize, int ctlOffset, unsigned char* tbl)
{
	int fileSizeCompressed = -1;
	GECompression gedecompress;
	gedecompress.SetGame(MORTALKOMBAT);
	gedecompress.SetCompressedBuffer(&ctl[ctlOffset], ctlSize);
	int fileSizeUncompressed;
	unsigned char* outputDecompressed = gedecompress.OutputDecompressedBuffer(fileSizeUncompressed, fileSizeCompressed);

	ALBank* alBank = NULL;
	if (outputDecompressed != NULL)
	{
		unsigned long fileSizeUncompressedLong = fileSizeUncompressed;
		alBank = ReadAudioN64PtrWavetableV2(&outputDecompressed[0], fileSizeUncompressedLong, 0, tbl);
		alBank->soundBankFormat = N64PTRWAVETABLETABLEV2ZLIB;
		delete [] outputDecompressed;
	}
	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioRawTest(unsigned char* rawData, int size)
{
	ALBank* alBank = new ALBank();
	alBank->soundBankFormat = STANDARDFORMAT;
	alBank->count = 1;
	alBank->flags = 0;
	alBank->pad = 0;
	alBank->samplerate = 11050;
	alBank->percussion = 0;
	
	alBank->inst = NULL;
	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = 0;

	if ((alBank->flags == 0x0000) || (alBank->flags == 0x0100)) // offset
	{
		alBank->inst = new ALInst*[alBank->count];

		for (int x = 0; x < alBank->count; x++)
		{
			alBank->inst[x] = new ALInst();
			alBank->inst[x]->samplerate = 0;
			alBank->inst[x]->sounds = NULL;
		}

		for (int x = 0; x < alBank->count; x++)
		{
			alBank->inst[x]->volume = 0;
			alBank->inst[x]->pan = 0;
			alBank->inst[x]->priority = 0;
			alBank->inst[x]->flags = 0;
			alBank->inst[x]->tremType = 0;
			alBank->inst[x]->tremRate = 0;
			alBank->inst[x]->tremDepth = 0;
			alBank->inst[x]->tremDelay = 0;
			alBank->inst[x]->vibType = 0;
			alBank->inst[x]->vibRate = 0;
			alBank->inst[x]->vibDepth = 0;
			alBank->inst[x]->vibDelay = 0;
			alBank->inst[x]->bendRange = 0;
			alBank->inst[x]->soundCount = 1;

			if ((alBank->inst[x]->flags == 0x0) || (alBank->inst[x]->flags == 0x1))
			{
				alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

				for (int y = 0; y < alBank->inst[x]->soundCount; y++)
				{
					alBank->inst[x]->sounds[y] = new ALSound();
					alBank->inst[x]->sounds[y]->wav.wavData = NULL;
				}

				for (int y = 0; y < alBank->inst[x]->soundCount; y++)
				{
					alBank->inst[x]->sounds[y]->samplePan = 0;
					alBank->inst[x]->sounds[y]->sampleVolume = 0;
					alBank->inst[x]->sounds[y]->flags = 0;

					
					if ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1))
					{
						alBank->inst[x]->sounds[y]->env.attackTime = 0;
						alBank->inst[x]->sounds[y]->env.decayTime = 0;
						alBank->inst[x]->sounds[y]->env.releaseTime = 0;
						alBank->inst[x]->sounds[y]->env.attackVolume = 0;
						alBank->inst[x]->sounds[y]->env.decayVolume = 0;

						alBank->inst[x]->sounds[y]->key.velocitymin = 0;
						alBank->inst[x]->sounds[y]->key.velocitymax = 0;
						alBank->inst[x]->sounds[y]->key.keymin = 0;
						alBank->inst[x]->sounds[y]->key.keymax = 0;
						alBank->inst[x]->sounds[y]->key.keybase = 0;
						alBank->inst[x]->sounds[y]->key.detune = 0;

						alBank->inst[x]->sounds[y]->wav.base = 0;
						alBank->inst[x]->sounds[y]->wav.len = size;
						alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];

						for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
						{
							alBank->inst[x]->sounds[y]->wav.wavData[r] = rawData[alBank->inst[x]->sounds[y]->wav.base + r];
						}
						

						alBank->inst[x]->sounds[y]->wav.type = AL_RAW16_WAVE;
						alBank->inst[x]->sounds[y]->wav.flags = 0;
						// MUST PAD to 4s

					
						alBank->inst[x]->sounds[y]->wav.rawWave = new ALRAWWaveInfo();
						alBank->inst[x]->sounds[y]->wav.rawWave->loop = NULL;
					}
					else
					{
						DisposeALBank(alBank);
						MessageBox(NULL, "Error", "Unsupported type in ALSound", NULL);
						return NULL;
					}
				}
			}
			else
			{
				DisposeALBank(alBank);
				MessageBox(NULL, "Error", "Unsupported inst type in ALInst", NULL);
				return NULL;
			}
		}
	}
	else
	{
		DisposeALBank(alBank);
		MessageBox(NULL, "Error", "Unsupported type in ALBank", NULL);
		return NULL;
	}

	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioVox(unsigned char* ctl, int ctlSize, int ctlOffset, unsigned char* tbl, int samplingRate)
{
	ALBank* alBank = new ALBank();
	alBank->soundBankFormat = VOX;
	alBank->count = 1;
	alBank->flags = 0;
	alBank->percussion = NULL;
	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = 0;

	int numberBanks = 1;
	alBank->inst = new ALInst*[numberBanks];

	alBank->inst[0] = new ALInst();
	alBank->inst[0]->samplerate = 44100;
	alBank->inst[0]->sounds = NULL;

	alBank->inst[0]->soundCount = 1;

	alBank->inst[0]->sounds = new ALSound*[alBank->inst[0]->soundCount];

	for (int y = 0; y < alBank->inst[0]->soundCount; y++)
	{
		alBank->inst[0]->sounds[y] = new ALSound();
		alBank->inst[0]->sounds[y]->wav.wavData = NULL;

		alBank->inst[0]->samplerate = samplingRate;
	}

	for (int y = 0; y < alBank->inst[0]->soundCount; y++)
	{
		alBank->inst[0]->sounds[y]->flags = 0;

		alBank->inst[0]->sounds[y]->wav.base = ctlOffset;
		alBank->inst[0]->sounds[y]->wav.len = ctlSize;
		alBank->inst[0]->sounds[y]->wav.wavData = new unsigned char[ctlSize];

		for (int  r = 0; r < alBank->inst[0]->sounds[y]->wav.len; r++)
		{
			alBank->inst[0]->sounds[y]->wav.wavData[r] = ctl[alBank->inst[0]->sounds[y]->wav.base + r];
		}
		

		alBank->inst[0]->sounds[y]->wav.type = AL_VOX_WAVE;
		alBank->inst[0]->sounds[y]->wav.flags = 0;
		// MUST PAD to 4s
		
		alBank->inst[0]->sounds[y]->wav.adpcmWave = NULL;
		alBank->inst[0]->sounds[y]->wav.rawWave = NULL;
	}

	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudio64dd(unsigned char* ctl, int ctlSize, int ctlOffset, unsigned char* tbl)
{
	unsigned long header = CharArrayToLong(&ctl[ctlOffset]);
	if (header != 0x19970123)
	{
		MessageBox(NULL, "Error", "Bad header for 64dd bank", NULL);
		return NULL;
	}

	int numberWaveforms = CharArrayToLong(&ctl[ctlOffset+4]);
	unsigned long wavePointer = ctlOffset + CharArrayToLong(&ctl[ctlOffset+8]);
	unsigned long bookPointer = ctlOffset + CharArrayToLong(&ctl[ctlOffset+0xC]);
	unsigned long loopPointer = ctlOffset + CharArrayToLong(&ctl[ctlOffset+0x10]);
	unsigned long bookDataPointer = ctlOffset + CharArrayToLong(&ctl[ctlOffset+0x14]);
	unsigned long loopDataPointer = ctlOffset + CharArrayToLong(&ctl[ctlOffset+0x18]);
	unsigned long informationPointer = ctlOffset + CharArrayToLong(&ctl[ctlOffset+0x1C]);

	ALBank* alBank = new ALBank();
	alBank->soundBankFormat = N64DD;
	alBank->count = numberWaveforms;
	alBank->flags = 0;
	alBank->percussion = NULL;
	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = 0;

	alBank->inst = new ALInst*[alBank->count];

	for (int x = 0; x < alBank->count; x++)
	{
		alBank->inst[x] = new ALInst();
		alBank->inst[x]->samplerate = 32000;
		alBank->inst[x]->sounds = NULL;

		alBank->inst[x]->soundCount = 1;

		alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

		for (int y = 0; y < alBank->inst[x]->soundCount; y++)
		{
			alBank->inst[x]->sounds[y] = new ALSound();
			alBank->inst[x]->sounds[y]->wav.wavData = NULL;
		}

		unsigned long wavePointerSound = ctlOffset + CharArrayToLong(&ctl[wavePointer + (x * 4)]);
		unsigned long bookPointerSound = ctlOffset + CharArrayToLong(&ctl[bookPointer + (x * 4)]);
		unsigned long loopPointerSound = ctlOffset + CharArrayToLong(&ctl[loopPointer + (x * 4)]);
		unsigned long informationPointerSound = informationPointer + (x * 0x20);

		WaveInformation waveInfo;
		waveInfo.version = CharArrayToLong(&ctl[informationPointerSound]);
		waveInfo.adpcmsize = CharArrayToLong(&ctl[informationPointerSound+4]);
		waveInfo.samplesize = CharArrayToLong(&ctl[informationPointerSound+8]);
		waveInfo.loop_startsamplepoint = CharArrayToLong(&ctl[informationPointerSound+0xC]);
		waveInfo.loop_endsamplepoint = CharArrayToLong(&ctl[informationPointerSound+0x10]);
		waveInfo.loop_count = CharArrayToShort(&ctl[informationPointerSound+0x14]);
		waveInfo.book_bytes = ctl[informationPointerSound+0x16];
		waveInfo.samplingbaseMIDIkey = ctl[informationPointerSound+0x17];
		waveInfo.samplingrate = CharArrayToFloat(&ctl[informationPointerSound+0x18]);
		waveInfo.tuning_C4_32K = CharArrayToFloat(&ctl[informationPointerSound+0x1C]);
		
		alBank->inst[x]->sounds[0]->flags = 0;

		alBank->inst[x]->sounds[0]->wav.sampleRateNotInDefaultNintendoSpec = waveInfo.samplingrate;
		alBank->inst[x]->sounds[0]->key.keybase = waveInfo.samplingbaseMIDIkey;
		alBank->inst[x]->sounds[0]->key.detune = waveInfo.tuning_C4_32K;

		alBank->inst[x]->sounds[0]->wav.base = wavePointerSound;
		alBank->inst[x]->sounds[0]->wav.len = waveInfo.adpcmsize;
		alBank->inst[x]->sounds[0]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[0]->wav.len];

		for (int  r = 0; r < alBank->inst[x]->sounds[0]->wav.len; r++)
		{
			alBank->inst[x]->sounds[0]->wav.wavData[r] = tbl[alBank->inst[x]->sounds[0]->wav.base + r];
		}
		

		alBank->inst[x]->sounds[0]->wav.type = AL_ADPCM_WAVE;
		alBank->inst[x]->sounds[0]->wav.flags = 0;
		// MUST PAD to 4s
		

		if ((alBank->inst[x]->sounds[0]->wav.type == AL_ADPCM_WAVE) && ((alBank->inst[x]->sounds[0]->flags == 0x0) || (alBank->inst[x]->sounds[0]->flags == 0x1)))
		{
			alBank->inst[x]->sounds[0]->wav.adpcmWave = new ALADPCMWaveInfo();
			
			alBank->inst[x]->sounds[0]->wav.adpcmWave->loop = new ALADPCMloop();
			alBank->inst[x]->sounds[0]->wav.adpcmWave->loop->start = waveInfo.loop_startsamplepoint;
			alBank->inst[x]->sounds[0]->wav.adpcmWave->loop->end = waveInfo.loop_endsamplepoint;
			alBank->inst[x]->sounds[0]->wav.adpcmWave->loop->count = waveInfo.loop_count;
			for (int z = 0; z < 0x10; z++)
			{
				alBank->inst[x]->sounds[0]->wav.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopPointerSound + z * 2]);
			}

			alBank->inst[x]->sounds[0]->wav.adpcmWave->book = new ALADPCMBook();
			alBank->inst[x]->sounds[0]->wav.adpcmWave->book->order = 2;
			alBank->inst[x]->sounds[0]->wav.adpcmWave->book->npredictors = 2;
			alBank->inst[x]->sounds[0]->wav.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[0]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[0]->wav.adpcmWave->book->npredictors * 8];

			for (int z = 0; z < alBank->inst[x]->sounds[0]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[0]->wav.adpcmWave->book->npredictors * 8; z++)
			{
				alBank->inst[x]->sounds[0]->wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[bookPointerSound + z * 2]);
			}
		}
		else
		{
			DisposeALBank(alBank);
			MessageBox(NULL, "Error", "Unsupported type in ALSound wav", NULL);
			return NULL;
		}
	}

	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioConker(unsigned char* ctl, int ctlSize, int ctlOffset, int ctlOffsetPartTwo, unsigned char* tbl)
{
	int fileSizeCompressed = -1;
	GECompression gedecompress;
	gedecompress.SetGame(CONKER);
	gedecompress.SetCompressedBuffer(&ctl[ctlOffset], ctlSize);
	int fileSizeUncompressed;
	unsigned char* ctlDecompressed = gedecompress.OutputDecompressedBuffer(fileSizeUncompressed, fileSizeCompressed);


	if (ctlDecompressed == NULL)
	{
		return NULL;
	}

	unsigned long bankOffset = 0x0;

	ALBank* alBank = new ALBank();
	alBank->soundBankFormat = CONKER;

	alBank->count = CharArrayToShort(&ctlDecompressed[bankOffset+0x8]);
	alBank->samplerate = CharArrayToShort(&ctlDecompressed[bankOffset+0xE]);

	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = 0;

	alBank->inst = new ALInst*[alBank->count];

	for (int x = 0; x < alBank->count; x++)
	{
		alBank->inst[x] = new ALInst();
		alBank->inst[x]->samplerate = 0;
		alBank->inst[x]->sounds = NULL;
	}

	for (int x = 0; x < alBank->count; x++)
	{
		unsigned long offsetInstrument = CharArrayToLong(&ctlDecompressed[0x14 + (x * 4)]);
		
		bool isSoundType = (offsetInstrument & 0x1);

		if (!isSoundType)
		{
			
			alBank->inst[x]->volume = ctlDecompressed[offsetInstrument];
			alBank->inst[x]->pan = ctlDecompressed[offsetInstrument+1];
			alBank->inst[x]->priority = ctlDecompressed[offsetInstrument+2];
			alBank->inst[x]->flags = ctlDecompressed[offsetInstrument+3];
			alBank->inst[x]->tremType = ctlDecompressed[offsetInstrument+4];
			alBank->inst[x]->tremRate = ctlDecompressed[offsetInstrument+5];
			alBank->inst[x]->tremDepth = ctlDecompressed[offsetInstrument+6];
			alBank->inst[x]->tremDelay = ctlDecompressed[offsetInstrument+7];
			alBank->inst[x]->vibType = ctlDecompressed[offsetInstrument+8];
			alBank->inst[x]->vibRate = ctlDecompressed[offsetInstrument+9];
			alBank->inst[x]->vibDepth = ctlDecompressed[offsetInstrument+0xA];
			alBank->inst[x]->vibDelay = ctlDecompressed[offsetInstrument+0xB];
			alBank->inst[x]->bendRange = CharArrayToShort(&ctlDecompressed[offsetInstrument+0xC]);
			alBank->inst[x]->soundCount = CharArrayToShort(&ctlDecompressed[offsetInstrument+0xE]);
		}
		else
		{
			offsetInstrument = ctlOffsetPartTwo + ((offsetInstrument >> 8) << 3);
			alBank->inst[x]->volume = ctl[offsetInstrument];
			alBank->inst[x]->pan = ctl[offsetInstrument+1];
			alBank->inst[x]->priority = ctl[offsetInstrument+2];
			alBank->inst[x]->flags = ctl[offsetInstrument+3];
			alBank->inst[x]->tremType = ctl[offsetInstrument+4];
			alBank->inst[x]->tremRate = ctl[offsetInstrument+5];
			alBank->inst[x]->tremDepth = ctl[offsetInstrument+6];
			alBank->inst[x]->tremDelay = ctl[offsetInstrument+7];
			alBank->inst[x]->vibType = ctl[offsetInstrument+8];
			alBank->inst[x]->vibRate = ctl[offsetInstrument+9];
			alBank->inst[x]->vibDepth = ctl[offsetInstrument+0xA];
			alBank->inst[x]->vibDelay = ctl[offsetInstrument+0xB];
			alBank->inst[x]->bendRange = CharArrayToShort(&ctl[offsetInstrument+0xC]);
			alBank->inst[x]->soundCount = CharArrayToShort(&ctl[offsetInstrument+0xE]);
		}
		alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

		for (int y = 0; y < alBank->inst[x]->soundCount; y++)
		{
			alBank->inst[x]->sounds[y] = new ALSound();
			alBank->inst[x]->sounds[y]->wav.wavData = NULL;
		}

		for (int y = 0; y < alBank->inst[x]->soundCount; y++)
		{
			unsigned long offsetSound;
			unsigned long baseOffsetSound;
			if (!isSoundType)
			{
				offsetSound = ctlOffsetPartTwo + (((CharArrayToLong(&ctlDecompressed[offsetInstrument+0x10+(y*4)])) >> 8) << 3);
				baseOffsetSound = offsetSound;
			}
			else
			{
				offsetSound = offsetInstrument + (CharArrayToLong(&ctl[offsetInstrument+0x10+(y*4)]));
				baseOffsetSound = offsetInstrument;
			}

			unsigned long offsetEnv = baseOffsetSound + CharArrayToLong(&ctl[offsetSound]);
			unsigned long offsetKey = baseOffsetSound + CharArrayToLong(&ctl[offsetSound+4]);
			unsigned long offsetWav = baseOffsetSound + CharArrayToLong(&ctl[offsetSound+8]);
			
			alBank->inst[x]->sounds[y]->env.attackTime = CharArrayToLong(&ctl[offsetEnv + 0x0]);
			alBank->inst[x]->sounds[y]->env.decayTime = CharArrayToLong(&ctl[offsetEnv + 0x4]);
			alBank->inst[x]->sounds[y]->env.releaseTime = CharArrayToLong(&ctl[offsetEnv + 0x8]);
			alBank->inst[x]->sounds[y]->env.attackVolume = CharArrayToShort(&ctl[offsetEnv + 0xC]);
			alBank->inst[x]->sounds[y]->env.decayVolume = CharArrayToShort(&ctl[offsetEnv + 0xE]);

			alBank->inst[x]->sounds[y]->key.velocitymin = ctl[offsetKey+0x0];
			alBank->inst[x]->sounds[y]->key.velocitymax = ctl[offsetKey+0x1];
			alBank->inst[x]->sounds[y]->key.keymin = ctl[offsetKey+0x2];
			alBank->inst[x]->sounds[y]->key.keymax = ctl[offsetKey+0x3];
			alBank->inst[x]->sounds[y]->key.keybase = ctl[offsetKey+0x4];
			alBank->inst[x]->sounds[y]->key.detune = ctl[offsetKey+0x5];

			alBank->inst[x]->sounds[y]->wav.base = CharArrayToLong(&ctl[offsetWav + 0x0]);
			alBank->inst[x]->sounds[y]->wav.len = CharArrayToLong(&ctl[offsetWav + 0x4]);
			alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];

			for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
			{
				alBank->inst[x]->sounds[y]->wav.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wav.base + r];
			}
			
			// MUST PAD to 4s

			alBank->inst[x]->sounds[y]->wav.adpcmWave = new ALADPCMWaveInfo();

			unsigned long loopOffset = CharArrayToLong(&ctl[offsetWav + 0xC]);

			if (loopOffset != 0)
			{
				loopOffset = baseOffsetSound + loopOffset;
				alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = new ALADPCMloop();
				alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
				alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
				alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);
				for (int z = 0; z < 0x10; z++)
				{
					alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffset + 0xC + z * 2]);
				}
			}
			else
			{
				alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = NULL;
			}

			unsigned long predictorOffset = CharArrayToLong(&ctl[offsetWav + 0x10]);

			if (predictorOffset != 0)
			{
				predictorOffset = baseOffsetSound + predictorOffset;
				alBank->inst[x]->sounds[y]->wav.adpcmWave->book = new ALADPCMBook();
				alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffset + 0x0]);
				alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffset + 0x4]);;
				alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8];

				for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8; z++)
				{
					alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + 8 + z * 2]);
				}
			}
		}
	}

	delete [] ctlDecompressed;

	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioBanjoTooie(unsigned char* ctl, int ctlSize, int ctlOffset, unsigned char* tbl, int ctlFlaggedOffset, unsigned long mask, int bankNumber)
{
	unsigned long bankOffset = ctlOffset;

	ALBank* alBank = new ALBank();
	alBank->soundBankFormat = BANJOTOOIEAUDIO;
	alBank->count = CharArrayToShort(&ctl[bankOffset]);
	alBank->flags = CharArrayToShort(&ctl[bankOffset+2]);
	alBank->pad = CharArrayToShort(&ctl[bankOffset+4]);
	alBank->samplerate = CharArrayToShort(&ctl[bankOffset+6]);

	unsigned long soundDataOffset = bankOffset + 8 + (alBank->count * 0x12);
	if ((soundDataOffset % 4) != 0)
	{
		soundDataOffset = soundDataOffset + (4 - (soundDataOffset % 4));
	}

	alBank->inst = NULL;
	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = 0;

	if ((alBank->flags == 0x0000) || (alBank->flags == 0x0100)) // offset
	{
		alBank->inst = new ALInst*[alBank->count];

		for (int x = 0; x < alBank->count; x++)
		{
			alBank->inst[x] = new ALInst();
			alBank->inst[x]->samplerate = 0;
			alBank->inst[x]->sounds = NULL;
		}

		for (int x = 0; x < alBank->count; x++)
		{
			unsigned long offsetInstrument = (bankOffset + 0x8 + x*0x12);

			alBank->inst[x]->volume = ctl[offsetInstrument];
			alBank->inst[x]->pan = ctl[offsetInstrument+1];
			alBank->inst[x]->priority = ctl[offsetInstrument+2];
			alBank->inst[x]->flags = ctl[offsetInstrument+3];
			alBank->inst[x]->tremType = ctl[offsetInstrument+4];
			alBank->inst[x]->tremRate = ctl[offsetInstrument+5];
			alBank->inst[x]->tremDepth = ctl[offsetInstrument+6];
			alBank->inst[x]->tremDelay = ctl[offsetInstrument+7];
			alBank->inst[x]->vibType = ctl[offsetInstrument+8];
			alBank->inst[x]->vibRate = ctl[offsetInstrument+9];
			alBank->inst[x]->vibDepth = ctl[offsetInstrument+0xA];
			alBank->inst[x]->vibDelay = ctl[offsetInstrument+0xB];
			alBank->inst[x]->bendRange = CharArrayToShort(&ctl[offsetInstrument+0xC]);
			alBank->inst[x]->soundCount = CharArrayToShort(&ctl[offsetInstrument+0xE]);

			if ((alBank->inst[x]->flags == 0x0) || (alBank->inst[x]->flags == 0x1))
			{	
				alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

				for (int y = 0; y < alBank->inst[x]->soundCount; y++)
				{
					alBank->inst[x]->sounds[y] = new ALSound();
					alBank->inst[x]->sounds[y]->wav.wavData = NULL;
				}

				for (int y = 0; y < alBank->inst[x]->soundCount; y++)
				{
					unsigned long offsetSound = soundDataOffset + (CharArrayToShort(&ctl[offsetInstrument + 0x10]) * 0xD8) + (0xD8 * y);
					
					if ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1))
					{
						alBank->inst[x]->sounds[y]->env.attackTime = CharArrayToLong(&ctl[offsetSound + 0x0]);
						alBank->inst[x]->sounds[y]->env.decayTime = CharArrayToLong(&ctl[offsetSound + 0x4]);
						alBank->inst[x]->sounds[y]->env.releaseTime = CharArrayToLong(&ctl[offsetSound + 0x8]);
						alBank->inst[x]->sounds[y]->env.attackVolume = CharArrayToShort(&ctl[offsetSound + 0xC]);
						alBank->inst[x]->sounds[y]->env.decayVolume = CharArrayToShort(&ctl[offsetSound + 0xE]);

						alBank->inst[x]->sounds[y]->key.velocitymin = ctl[offsetSound+0x10];
						alBank->inst[x]->sounds[y]->key.velocitymax = ctl[offsetSound+0x11];
						alBank->inst[x]->sounds[y]->key.keymin = ctl[offsetSound+0x12];
						alBank->inst[x]->sounds[y]->key.keymax = ctl[offsetSound+0x13];
						alBank->inst[x]->sounds[y]->key.keybase = ctl[offsetSound+0x14];
						alBank->inst[x]->sounds[y]->key.detune = ctl[offsetSound+0x15];

						alBank->inst[x]->sounds[y]->wav.base = CharArrayToLong(&ctl[offsetSound + 0x18]);
						alBank->inst[x]->sounds[y]->wav.len = CharArrayToLong(&ctl[offsetSound + 0x1C]);
						alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];

						for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
						{
							alBank->inst[x]->sounds[y]->wav.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wav.base + r];
						}
						
						// MUST PAD to 4s

						alBank->inst[x]->sounds[y]->wav.adpcmWave = new ALADPCMWaveInfo();
						unsigned long loopOffset = offsetSound + 0x20;
						if ((CharArrayToLong(&ctl[loopOffset]) == 0x00000000) && (CharArrayToLong(&ctl[loopOffset+4]) == 0x00000000) && (CharArrayToLong(&ctl[loopOffset+8]) == 0x00000000))
						{
							loopOffset = 0;
						}

						unsigned long predictorOffset = offsetSound + 0x50;

						if (loopOffset != 0)
						{						
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = new ALADPCMloop();
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);
							for (int z = 0; z < 0x10; z++)
							{
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffset + 0xC + z * 2]);
							}
						}
						else
						{
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = NULL;
						}

						if (predictorOffset != 0)
						{
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book = new ALADPCMBook();
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order = 0x2;
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors = 0x4;
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8];

							for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8; z++)
							{
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + z * 2]);
							}
						}
					}
					else
					{
						DisposeALBank(alBank);
						MessageBox(NULL, "Error", "Unsupported type in ALSound", NULL);
						return NULL;
					}
				}
			}
			else
			{
				DisposeALBank(alBank);
				MessageBox(NULL, "Error", "Unsupported inst type in ALInst", NULL);
				return NULL;
			}
		}
	}
	else
	{
		DisposeALBank(alBank);
		MessageBox(NULL, "Error", "Unsupported type in ALBank", NULL);
		return NULL;
	}

	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioZLibMusyxSmall(unsigned char* ctl, int ctlSize, int ctlOffset, unsigned char* tbl, int numberInstruments, int lastSoundEnd)
{
	int fileSizeCompressed = -1;
	GECompression gedecompress;
	gedecompress.SetGame(ROGUESQUADRON);
	gedecompress.SetCompressedBuffer(&ctl[ctlOffset], ctlSize);
	int fileSizeUncompressed;
	unsigned char* outputDecompressed = gedecompress.OutputDecompressedBuffer(fileSizeUncompressed, fileSizeCompressed);
	if (outputDecompressed != NULL)
	{
		ALBank* alBank = ReadAudioMusyxSmallerTable(&outputDecompressed[0], fileSizeUncompressed, 0, tbl, numberInstruments, lastSoundEnd);
		alBank->soundBankFormat = MUSYXSMALLZLIB;
		delete [] outputDecompressed;
		return alBank;
	}
	else
	{
		return NULL;
	}
}

ALBank* CN64AIFCAudio::ReadAudioZLibMusyx78DA(unsigned char* ctl, int ctlSize, int ctlOffset, unsigned char* tbl, int numberInstruments, int lastSoundEnd)
{
	int fileSizeCompressed = -1;
	GECompression gedecompress;
	gedecompress.SetGame(ROGUESQUADRON);
	gedecompress.SetCompressedBuffer(&ctl[ctlOffset], ctlSize);
	int fileSizeUncompressed;
	unsigned char* outputDecompressed = gedecompress.OutputDecompressedBuffer(fileSizeUncompressed, fileSizeCompressed);
	if (outputDecompressed != NULL)
	{
		ALBank* alBank = ReadAudioMusyx(&outputDecompressed[0], fileSizeUncompressed, 0, tbl, numberInstruments, lastSoundEnd);
		alBank->soundBankFormat = MUSYXZLIB;
		delete [] outputDecompressed;
		return alBank;
	}
	else
	{
		return NULL;
	}
}

ALBank* CN64AIFCAudio::ReadAudioZLibMusyx(unsigned char* ctl, int ctlSize, int ctlOffset, unsigned char* tbl, int numberInstruments, int lastSoundEnd, int game)
{
	int fileSizeCompressed = -1;
	GECompression gedecompress;
	gedecompress.SetGame(game);
	gedecompress.SetCompressedBuffer(&ctl[ctlOffset], ctlSize);
	int fileSizeUncompressed;
	unsigned char* outputDecompressed = gedecompress.OutputDecompressedBuffer(fileSizeUncompressed, fileSizeCompressed);
	if (outputDecompressed != NULL)
	{
		ALBank* alBank = ReadAudioMusyx(&outputDecompressed[0], fileSizeUncompressed, 0, tbl, numberInstruments, lastSoundEnd);
		alBank->soundBankFormat = MUSYXZLIB;
		delete [] outputDecompressed;
		return alBank;
	}
	else
	{
		return NULL;
	}
}

ALBank* CN64AIFCAudio::ReadAudioBlastCorps(unsigned char* ROM, unsigned char* ctl, int ctlSize, int ctlOffset, unsigned char* tbl)
{
	unsigned char* outputDecompressed = new unsigned char[0x1000000];
	int fileSizeCompressed = ctlSize;
	BlastCorpsLZBDecoder blastCorpsLzb;
	int decompressedSize = blastCorpsLzb.dec(&ctl[ctlOffset], outputDecompressed, fileSizeCompressed);
	ALBank* alBank = ReadAudio(ROM, &outputDecompressed[0], decompressedSize, 0, tbl, 0x0, 0x0, 0);
	alBank->soundBankFormat = BLASTCORPSZLBSTANDARD;
	delete [] outputDecompressed;
	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioLzMusyx(unsigned char* ctl, int ctlSize, int ctlOffset, unsigned char* tbl, int numberInstruments, int lastSoundEnd)
{
	unsigned char* outputDecompressed = new unsigned char[0x1000000];
	int fileSizeCompressed = ctlSize;
	MidwayLZ midwayLz;
	int decompressedSize = midwayLz.dec(&ctl[ctlOffset], fileSizeCompressed, outputDecompressed);
	ALBank* alBank = ReadAudioMusyx(&outputDecompressed[0], decompressedSize, 0, tbl, numberInstruments, lastSoundEnd);
	alBank->soundBankFormat = MUSYXLZ;
	delete [] outputDecompressed;
	return alBank;
}

// Full credit to Musyx goes to Bobby Smiles (from Mupen emulator)

ALBank* CN64AIFCAudio::ReadAudioMusyxSmallerTable(unsigned char* ctl, int ctlSize, int ctlOffset, unsigned char* tbl, int numberInstruments, int lastSoundEnd)
{
	ALBank* alBank = new ALBank();
	alBank->soundBankFormat = MUSYX;
	alBank->count = numberInstruments;
	alBank->flags = 0;
	alBank->pad = 0;
	alBank->samplerate = 0x2B11;
	alBank->percussion = 0;
	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = 0;

	alBank->inst = new ALInst*[alBank->count];

	for (int x = 0; x < alBank->count; x++)
	{
		alBank->inst[x] = new ALInst();
		alBank->inst[x]->samplerate = 0;
		alBank->inst[x]->sounds = NULL;
	}

	for (int x = 0; x < alBank->count; x++)
	{
		unsigned long offsetInstrument = ctlOffset + x*0x18;
	
		alBank->inst[x]->soundCount = 1;

		alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

		for (int y = 0; y < alBank->inst[x]->soundCount; y++)
		{
			alBank->inst[x]->sounds[y] = new ALSound();
			alBank->inst[x]->sounds[y]->wav.wavData = NULL;
		}

		for (int y = 0; y < alBank->inst[x]->soundCount; y++)
		{
			alBank->inst[x]->sounds[y]->wav.adpcmWave = new ALADPCMWaveInfo();
			alBank->inst[x]->sounds[y]->wav.type = AL_MUSYX_WAVE;

			alBank->inst[x]->samplerate = CharArrayToShort(&ctl[offsetInstrument+0xA]);
			alBank->inst[x]->sounds[y]->wav.sampleRateNotInDefaultNintendoSpec = CharArrayToShort(&ctl[offsetInstrument+0xE]);

			alBank->inst[x]->sounds[y]->key.keybase = ctl[offsetInstrument + 0x8];

			unsigned long predictorOffset = CharArrayToLong(&ctl[offsetInstrument+4]);

			alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = NULL;

			alBank->inst[x]->sounds[y]->wav.adpcmWave->book = new ALADPCMBook();
			alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order = 2;
			alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors = 8;
			alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8];

			for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8; z++)
			{
				alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&tbl[predictorOffset + z * 2]);
			}

			alBank->inst[x]->sounds[y]->wav.base = predictorOffset + (alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 0x10);
			if (x == (alBank->count-1))
			{
				alBank->inst[x]->sounds[y]->wav.len = lastSoundEnd - CharArrayToLong(&ctl[offsetInstrument+0x4]);
			}
			else
			{
				alBank->inst[x]->sounds[y]->wav.len = CharArrayToLong(&ctl[offsetInstrument+0x18 + 0x4]) - CharArrayToLong(&ctl[offsetInstrument+0x4]);
			}

			alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];

			for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
			{
				alBank->inst[x]->sounds[y]->wav.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wav.base + r];
			}
		}
	}

	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioMusyx(unsigned char* ctl, int ctlSize, int ctlOffset, unsigned char* tbl, int numberInstruments, int lastSoundEnd)
{
	ALBank* alBank = new ALBank();
	alBank->soundBankFormat = MUSYX;
	alBank->count = numberInstruments;
	alBank->flags = 0;
	alBank->pad = 0;
	alBank->samplerate = 0x2B11;
	alBank->percussion = 0;
	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = 0;

	alBank->inst = new ALInst*[alBank->count];

	for (int x = 0; x < alBank->count; x++)
	{
		alBank->inst[x] = new ALInst();
		alBank->inst[x]->samplerate = 0;
		alBank->inst[x]->sounds = NULL;
	}

	for (int x = 0; x < alBank->count; x++)
	{
		unsigned long offsetInstrument = ctlOffset + x*0x1C;
	
		alBank->inst[x]->soundCount = 1;

		alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

		for (int y = 0; y < alBank->inst[x]->soundCount; y++)
		{
			alBank->inst[x]->sounds[y] = new ALSound();
			alBank->inst[x]->sounds[y]->wav.wavData = NULL;
		}

		for (int y = 0; y < alBank->inst[x]->soundCount; y++)
		{
			alBank->inst[x]->sounds[y]->wav.adpcmWave = new ALADPCMWaveInfo();
			alBank->inst[x]->sounds[y]->wav.type = AL_MUSYX_WAVE;

			alBank->inst[x]->samplerate = CharArrayToShort(&ctl[offsetInstrument+0xE]);
			alBank->inst[x]->sounds[y]->wav.sampleRateNotInDefaultNintendoSpec = CharArrayToShort(&ctl[offsetInstrument+0x12]);

			alBank->inst[x]->sounds[y]->key.keybase = ctl[offsetInstrument + 0xC];

			unsigned long predictorOffset = CharArrayToLong(&ctl[offsetInstrument+4]);

			alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = NULL;

			alBank->inst[x]->sounds[y]->wav.adpcmWave->book = new ALADPCMBook();
			alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order = 2;
			alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors = 8;
			alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8];

			for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8; z++)
			{
				alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&tbl[predictorOffset + z * 2]);
			}

			alBank->inst[x]->sounds[y]->wav.base = predictorOffset + (alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 0x10);
			if (x == (alBank->count-1))
			{
				alBank->inst[x]->sounds[y]->wav.len = lastSoundEnd - CharArrayToLong(&ctl[offsetInstrument+0x4]);
			}
			else
			{
				alBank->inst[x]->sounds[y]->wav.len = CharArrayToLong(&ctl[offsetInstrument+0x1C + 0x4]) - CharArrayToLong(&ctl[offsetInstrument+0x4]);
			}

			alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];

			for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
			{
				alBank->inst[x]->sounds[y]->wav.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wav.base + r];
			}
		}
	}

	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudio(unsigned char* ROM, unsigned char* ctl, int ctlSize, int ctlOffset, unsigned char* tbl, int ctlFlaggedOffset, unsigned long mask, int bankNumber)
{
	unsigned short numberBands = CharArrayToShort(&ctl[ctlOffset+0x2]);
	unsigned long bankOffset = CharArrayToLong(&ctl[ctlOffset+ 0x4 + (bankNumber * 0x4)]);
	if (((bankOffset >> 16) & 0xF0) > 0)
		bankOffset = ctlFlaggedOffset + (bankOffset - mask);
	else
		bankOffset = ctlOffset + bankOffset;

	ALBank* alBank = new ALBank();
	alBank->soundBankFormat = STANDARDFORMAT;
	alBank->count = CharArrayToShort(&ctl[bankOffset]);
	alBank->flags = CharArrayToShort(&ctl[bankOffset+2]);
	alBank->pad = CharArrayToShort(&ctl[bankOffset+4]);
	alBank->samplerate = CharArrayToShort(&ctl[bankOffset+6]);
	unsigned long offsetPercussion = CharArrayToLong(&ctl[bankOffset+8]);
	if (offsetPercussion != NULL)
	{
		alBank->percussion = new ALInst();
		alBank->percussion->samplerate = 0;
		alBank->percussion->sounds = NULL;

		if (alBank->flags == 0x0100)
			offsetPercussion = ctlFlaggedOffset + (offsetPercussion - mask);
		else
			offsetPercussion = ctlOffset + offsetPercussion;

		alBank->percussion->volume = ctl[offsetPercussion];
		alBank->percussion->pan = ctl[offsetPercussion+1];
		alBank->percussion->priority = ctl[offsetPercussion+2];
		alBank->percussion->flags = ctl[offsetPercussion+3];
		alBank->percussion->tremType = ctl[offsetPercussion+4];
		alBank->percussion->tremRate = ctl[offsetPercussion+5];
		alBank->percussion->tremDepth = ctl[offsetPercussion+6];
		alBank->percussion->tremDelay = ctl[offsetPercussion+7];
		alBank->percussion->vibType = ctl[offsetPercussion+8];
		alBank->percussion->vibRate = ctl[offsetPercussion+9];
		alBank->percussion->vibDepth = ctl[offsetPercussion+0xA];
		alBank->percussion->vibDelay = ctl[offsetPercussion+0xB];
		alBank->percussion->bendRange = CharArrayToShort(&ctl[offsetPercussion+0xC]);
		alBank->percussion->soundCount = CharArrayToShort(&ctl[offsetPercussion+0xE]);

		if ((alBank->percussion->flags == 0x0) || (alBank->percussion->flags == 0x1))
		{	
			alBank->percussion->sounds = new ALSound*[alBank->percussion->soundCount];

			for (int y = 0; y < alBank->percussion->soundCount; y++)
			{
				alBank->percussion->sounds[y] = new ALSound();
				alBank->percussion->sounds[y]->wav.wavData = NULL;
			}

			for (int y = 0; y < alBank->percussion->soundCount; y++)
			{
				unsigned long offsetSound = CharArrayToLong(&ctl[offsetPercussion+ 0x10 + y*0x4]);
				if (alBank->percussion->flags == 0x1)
					offsetSound = ctlFlaggedOffset + (offsetSound - mask);
				else
					offsetSound = ctlOffset + offsetSound;

				alBank->percussion->sounds[y]->samplePan = ctl[offsetSound+0xC];
				alBank->percussion->sounds[y]->sampleVolume = ctl[offsetSound+0xD];
				alBank->percussion->sounds[y]->flags = ctl[offsetSound+0xE];

				
				if ((alBank->percussion->sounds[y]->flags == 0x0) || (alBank->percussion->sounds[y]->flags == 0x1))
				{
					unsigned long offsetEnv = CharArrayToLong(&ctl[offsetSound+ 0x0]);
					if (alBank->percussion->sounds[y]->flags == 0x1)
						offsetEnv = ctlFlaggedOffset + (offsetEnv - mask);
					else
						offsetEnv = ctlOffset + offsetEnv;

					unsigned long offsetKeyMap = CharArrayToLong(&ctl[offsetSound+ 0x4]);
					if (alBank->percussion->sounds[y]->flags == 0x1)
						offsetKeyMap = ctlFlaggedOffset + (offsetKeyMap - mask);
					else
						offsetKeyMap = ctlOffset + offsetKeyMap;

					unsigned long offsetWaveTable = CharArrayToLong(&ctl[offsetSound+ 0x8]);
					if (alBank->percussion->sounds[y]->flags == 0x1)
						offsetWaveTable = ctlFlaggedOffset + (offsetWaveTable - mask);
					else
						offsetWaveTable = ctlOffset + offsetWaveTable;

					alBank->percussion->sounds[y]->env.attackTime = CharArrayToLong(&ctl[offsetEnv + 0x0]);
					alBank->percussion->sounds[y]->env.decayTime = CharArrayToLong(&ctl[offsetEnv + 0x4]);
					alBank->percussion->sounds[y]->env.releaseTime = CharArrayToLong(&ctl[offsetEnv + 0x8]);
					alBank->percussion->sounds[y]->env.attackVolume = ctl[offsetEnv + 0xC];
					alBank->percussion->sounds[y]->env.decayVolume = ctl[offsetEnv + 0xD];
					alBank->percussion->sounds[y]->env.zeroPad = CharArrayToShort(&ctl[offsetEnv + 0xE]);

					alBank->percussion->sounds[y]->key.velocitymin = ctl[offsetKeyMap];
					alBank->percussion->sounds[y]->key.velocitymax = ctl[offsetKeyMap+0x1];
					alBank->percussion->sounds[y]->key.keymin = ctl[offsetKeyMap+0x2];
					alBank->percussion->sounds[y]->key.keymax = ctl[offsetKeyMap+0x3];
					alBank->percussion->sounds[y]->key.keybase = ctl[offsetKeyMap+0x4];
					alBank->percussion->sounds[y]->key.detune = ctl[offsetKeyMap+0x5];

					unsigned char flag = CharArrayToLong(&ctl[offsetWaveTable + 0x0]) >> 24; // hack for NUD-DSCJ-JPN, can't imagine impact others
					if (flag == 0x40) // Means using 64DD IPL Bank
						alBank->percussion->sounds[y]->wav.base = (CharArrayToLong(&ctl[offsetWaveTable + 0x0]) & 0xFFFFFF) + 0x140000;
					else
						alBank->percussion->sounds[y]->wav.base = CharArrayToLong(&ctl[offsetWaveTable + 0x0]);
					alBank->percussion->sounds[y]->wav.len = CharArrayToLong(&ctl[offsetWaveTable + 0x4]);
					alBank->percussion->sounds[y]->wav.wavData = new unsigned char[alBank->percussion->sounds[y]->wav.len];

					for (int  r = 0; r < alBank->percussion->sounds[y]->wav.len; r++)
					{
						if (flag == 0x40)
						{
							alBank->percussion->sounds[y]->wav.wavData[r] = ROM[alBank->percussion->sounds[y]->wav.base + r];
						}
						else
						{
							alBank->percussion->sounds[y]->wav.wavData[r] = tbl[alBank->percussion->sounds[y]->wav.base + r];
						}
					}
					

					alBank->percussion->sounds[y]->wav.type = ctl[offsetWaveTable + 0x8];
					alBank->percussion->sounds[y]->wav.flags = ctl[offsetWaveTable + 0x9];
					// MUST PAD to 4s

					if ((alBank->percussion->sounds[y]->wav.type == AL_ADPCM_WAVE) && ((alBank->percussion->sounds[y]->flags == 0x0) || (alBank->percussion->sounds[y]->flags == 0x1)))
					{
						alBank->percussion->sounds[y]->wav.adpcmWave = new ALADPCMWaveInfo();
						unsigned long loopOffset = CharArrayToLong(&ctl[offsetWaveTable + 0xC]);
						unsigned long predictorOffset = CharArrayToLong(&ctl[offsetWaveTable + 0x10]);

						if (loopOffset != 0)
						{
							if (alBank->percussion->sounds[y]->flags == 0x1)
								loopOffset = ctlFlaggedOffset + (loopOffset - mask);
							else
								loopOffset = ctlOffset + loopOffset;

							alBank->percussion->sounds[y]->wav.adpcmWave->loop = new ALADPCMloop();
							alBank->percussion->sounds[y]->wav.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
							alBank->percussion->sounds[y]->wav.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
							alBank->percussion->sounds[y]->wav.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);
							for (int z = 0; z < 0x10; z++)
							{
								alBank->percussion->sounds[y]->wav.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffset + 0xC + z * 2]);
							}
						}
						else
						{
							alBank->percussion->sounds[y]->wav.adpcmWave->loop = NULL;
						}

						if (predictorOffset != 0)
						{
							if (alBank->percussion->sounds[y]->flags == 0x1)
								predictorOffset = ctlFlaggedOffset + (predictorOffset - mask);
							else
								predictorOffset = ctlOffset + predictorOffset;

							alBank->percussion->sounds[y]->wav.adpcmWave->book = new ALADPCMBook();
							alBank->percussion->sounds[y]->wav.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffset + 0x0]);
							alBank->percussion->sounds[y]->wav.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffset + 0x4]);
							alBank->percussion->sounds[y]->wav.adpcmWave->book->predictors = new signed short[alBank->percussion->sounds[y]->wav.adpcmWave->book->order * alBank->percussion->sounds[y]->wav.adpcmWave->book->npredictors * 8];

							for (int z = 0; z < alBank->percussion->sounds[y]->wav.adpcmWave->book->order * alBank->percussion->sounds[y]->wav.adpcmWave->book->npredictors * 8; z++)
							{
								alBank->percussion->sounds[y]->wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + 0x8 + z * 2]);
							}
						}
					}
					else if ((alBank->percussion->sounds[y]->flags == 0x0) || (alBank->percussion->sounds[y]->flags == 0x1))
					{
						alBank->percussion->sounds[y]->wav.rawWave = new ALRAWWaveInfo();
						unsigned long loopOffset = CharArrayToLong(&ctl[offsetWaveTable + 0xC]);

						if (loopOffset != 0)
						{
							if (alBank->percussion->sounds[y]->flags == 0x1)
								loopOffset = ctlFlaggedOffset + (loopOffset - mask);
							else
								loopOffset = ctlOffset + loopOffset;

							alBank->percussion->sounds[y]->wav.rawWave->loop = new ALRawLoop();
							alBank->percussion->sounds[y]->wav.rawWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
							alBank->percussion->sounds[y]->wav.rawWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
							alBank->percussion->sounds[y]->wav.rawWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);	
						}
						else
						{
							alBank->percussion->sounds[y]->wav.rawWave->loop = NULL;
						}
					}
					else
					{
						DisposeALBank(alBank);
						MessageBox(NULL, "Error", "Unsupported type in ALSound wav", NULL);
						return NULL;
					}
				}
				else
				{
					DisposeALBank(alBank);
					MessageBox(NULL, "Error", "Unsupported type in ALSound", NULL);
					return NULL;
				}
			}
		}
		else
		{
			DisposeALBank(alBank);
			MessageBox(NULL, "Error", "Unsupported inst type in ALInst", NULL);
			return NULL;
		}
	}

	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = 0;
	
	alBank->inst = NULL;

	if ((alBank->flags == 0x0000) || (alBank->flags == 0x0100)) // offset
	{
		alBank->inst = new ALInst*[alBank->count];

		for (int x = 0; x < alBank->count; x++)
		{
			alBank->inst[x] = new ALInst();
			alBank->inst[x]->samplerate = 0;
			alBank->inst[x]->sounds = NULL;
		}

		for (int x = 0; x < alBank->count; x++)
		{
			unsigned long offsetInstrument = CharArrayToLong(&ctl[bankOffset+ 0xC + x*4]);
			if (offsetInstrument == 0x0000)
			{
				alBank->inst[x]->soundCount = 0;
				alBank->inst[x]->sounds = NULL;
				continue;
			}

			if (alBank->flags == 0x0100)
				offsetInstrument = ctlFlaggedOffset + (offsetInstrument - mask);
			else
				offsetInstrument = ctlOffset + offsetInstrument;

			alBank->inst[x]->volume = ctl[offsetInstrument];
			alBank->inst[x]->pan = ctl[offsetInstrument+1];
			alBank->inst[x]->priority = ctl[offsetInstrument+2];
			alBank->inst[x]->flags = ctl[offsetInstrument+3];
			alBank->inst[x]->tremType = ctl[offsetInstrument+4];
			alBank->inst[x]->tremRate = ctl[offsetInstrument+5];
			alBank->inst[x]->tremDepth = ctl[offsetInstrument+6];
			alBank->inst[x]->tremDelay = ctl[offsetInstrument+7];
			alBank->inst[x]->vibType = ctl[offsetInstrument+8];
			alBank->inst[x]->vibRate = ctl[offsetInstrument+9];
			alBank->inst[x]->vibDepth = ctl[offsetInstrument+0xA];
			alBank->inst[x]->vibDelay = ctl[offsetInstrument+0xB];
			alBank->inst[x]->bendRange = CharArrayToShort(&ctl[offsetInstrument+0xC]);
			alBank->inst[x]->soundCount = CharArrayToShort(&ctl[offsetInstrument+0xE]);

			if ((alBank->inst[x]->flags == 0x0) || (alBank->inst[x]->flags == 0x1))
			{	
				alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

				for (int y = 0; y < alBank->inst[x]->soundCount; y++)
				{
					alBank->inst[x]->sounds[y] = new ALSound();
					alBank->inst[x]->sounds[y]->wav.wavData = NULL;
				}

				for (int y = 0; y < alBank->inst[x]->soundCount; y++)
				{
					unsigned long offsetSound = CharArrayToLong(&ctl[offsetInstrument+ 0x10 + y*0x4]);
					if (alBank->inst[x]->flags == 0x1)
						offsetSound = ctlFlaggedOffset + (offsetSound - mask);
					else
						offsetSound = ctlOffset + offsetSound;

					alBank->inst[x]->sounds[y]->samplePan = ctl[offsetSound+0xC];
					alBank->inst[x]->sounds[y]->sampleVolume = ctl[offsetSound+0xD];
					alBank->inst[x]->sounds[y]->flags = ctl[offsetSound+0xE];

					
					if ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1))
					{
						unsigned long offsetEnv = CharArrayToLong(&ctl[offsetSound+ 0x0]);
						if (alBank->inst[x]->sounds[y]->flags == 0x1)
							offsetEnv = ctlFlaggedOffset + (offsetEnv - mask);
						else
							offsetEnv = ctlOffset + offsetEnv;

						unsigned long offsetKeyMap = CharArrayToLong(&ctl[offsetSound+ 0x4]);
						if (alBank->inst[x]->sounds[y]->flags == 0x1)
							offsetKeyMap = ctlFlaggedOffset + (offsetKeyMap - mask);
						else
							offsetKeyMap = ctlOffset + offsetKeyMap;

						unsigned long offsetWaveTable = CharArrayToLong(&ctl[offsetSound+ 0x8]);
						if (alBank->inst[x]->sounds[y]->flags == 0x1)
							offsetWaveTable = ctlFlaggedOffset + (offsetWaveTable - mask);
						else
							offsetWaveTable = ctlOffset + offsetWaveTable;

						alBank->inst[x]->sounds[y]->env.attackTime = CharArrayToLong(&ctl[offsetEnv + 0x0]);
						alBank->inst[x]->sounds[y]->env.decayTime = CharArrayToLong(&ctl[offsetEnv + 0x4]);
						alBank->inst[x]->sounds[y]->env.releaseTime = CharArrayToLong(&ctl[offsetEnv + 0x8]);
						alBank->inst[x]->sounds[y]->env.attackVolume = ctl[offsetEnv + 0xC];
						alBank->inst[x]->sounds[y]->env.decayVolume = ctl[offsetEnv + 0xD];
						alBank->inst[x]->sounds[y]->env.zeroPad = CharArrayToShort(&ctl[offsetEnv + 0xE]);

						alBank->inst[x]->sounds[y]->key.velocitymin = ctl[offsetKeyMap];
						alBank->inst[x]->sounds[y]->key.velocitymax = ctl[offsetKeyMap+0x1];
						alBank->inst[x]->sounds[y]->key.keymin = ctl[offsetKeyMap+0x2];
						alBank->inst[x]->sounds[y]->key.keymax = ctl[offsetKeyMap+0x3];
						alBank->inst[x]->sounds[y]->key.keybase = ctl[offsetKeyMap+0x4];
						alBank->inst[x]->sounds[y]->key.detune = ctl[offsetKeyMap+0x5];

						unsigned char flag = CharArrayToLong(&ctl[offsetWaveTable + 0x0]) >> 24; // hack for NUD-DSCJ-JPN, can't imagine impact others
						if (flag == 0x40) // Means using 64DD IPL Bank
							alBank->inst[x]->sounds[y]->wav.base = (CharArrayToLong(&ctl[offsetWaveTable + 0x0]) & 0xFFFFFF) + 0x140000;
						else
							alBank->inst[x]->sounds[y]->wav.base = CharArrayToLong(&ctl[offsetWaveTable + 0x0]);
						alBank->inst[x]->sounds[y]->wav.len = CharArrayToLong(&ctl[offsetWaveTable + 0x4]);
						alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];

						for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
						{
							if (flag == 0x40)
							{
								alBank->inst[x]->sounds[y]->wav.wavData[r] = ROM[alBank->inst[x]->sounds[y]->wav.base + r];
							}
							else
							{
								alBank->inst[x]->sounds[y]->wav.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wav.base + r];
							}
						}
						

						alBank->inst[x]->sounds[y]->wav.type = ctl[offsetWaveTable + 0x8];
						alBank->inst[x]->sounds[y]->wav.flags = ctl[offsetWaveTable + 0x9];
						// MUST PAD to 4s

						if ((alBank->inst[x]->sounds[y]->wav.type == AL_ADPCM_WAVE) && ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1)))
						{
							alBank->inst[x]->sounds[y]->wav.adpcmWave = new ALADPCMWaveInfo();
							unsigned long loopOffset = CharArrayToLong(&ctl[offsetWaveTable + 0xC]);
							unsigned long predictorOffset = CharArrayToLong(&ctl[offsetWaveTable + 0x10]);

							if (loopOffset != 0)
							{
								if (alBank->inst[x]->sounds[y]->flags == 0x1)
									loopOffset = ctlFlaggedOffset + (loopOffset - mask);
								else
									loopOffset = ctlOffset + loopOffset;

								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = new ALADPCMloop();
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);
								for (int z = 0; z < 0x10; z++)
								{
									alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffset + 0xC + z * 2]);
								}
							}
							else
							{
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = NULL;
							}

							if (predictorOffset != 0)
							{
								if (alBank->inst[x]->sounds[y]->flags == 0x1)
									predictorOffset = ctlFlaggedOffset + (predictorOffset - mask);
								else
									predictorOffset = ctlOffset + predictorOffset;

								alBank->inst[x]->sounds[y]->wav.adpcmWave->book = new ALADPCMBook();
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffset + 0x0]);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffset + 0x4]);
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8];

								for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8; z++)
								{
									alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + 0x8 + z * 2]);
								}
							}
						}
						else if ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1))
						{
							alBank->inst[x]->sounds[y]->wav.rawWave = new ALRAWWaveInfo();
							unsigned long loopOffset = CharArrayToLong(&ctl[offsetWaveTable + 0xC]);

							if (loopOffset != 0)
							{
								if (alBank->inst[x]->sounds[y]->flags == 0x1)
									loopOffset = ctlFlaggedOffset + (loopOffset - mask);
								else
									loopOffset = ctlOffset + loopOffset;

								alBank->inst[x]->sounds[y]->wav.rawWave->loop = new ALRawLoop();
								alBank->inst[x]->sounds[y]->wav.rawWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
								alBank->inst[x]->sounds[y]->wav.rawWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
								alBank->inst[x]->sounds[y]->wav.rawWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);	
							}
							else
							{
								alBank->inst[x]->sounds[y]->wav.rawWave->loop = NULL;
							}
						}
						else
						{
							DisposeALBank(alBank);
							MessageBox(NULL, "Error", "Unsupported type in ALSound wav", NULL);
							return NULL;
						}
					}
					else
					{
						DisposeALBank(alBank);
						MessageBox(NULL, "Error", "Unsupported type in ALSound", NULL);
						return NULL;
					}
				}
			}
			else
			{
				DisposeALBank(alBank);
				MessageBox(NULL, "Error", "Unsupported inst type in ALInst", NULL);
				return NULL;
			}
		}
	}
	else
	{
		DisposeALBank(alBank);
		MessageBox(NULL, "Error", "Unsupported type in ALBank", NULL);
		return NULL;
	}

	return alBank;
}

ALBank* CN64AIFCAudio::ReadAudioMarioParty2E(unsigned char* ROM, unsigned char* ctl, int ctlSize, int ctlOffset, unsigned char* tbl, int ctlFlaggedOffset, unsigned long mask)
{
	unsigned short numberBands = CharArrayToShort(&ctl[ctlOffset+0x2]);
	unsigned long bankOffset = ctlOffset;

	ALBank* alBank = new ALBank();
	alBank->soundBankFormat = MARIOPARTY2E;
	alBank->count = 1;
	alBank->flags = 0;
	alBank->pad = 0;
	alBank->samplerate = 22050;
	alBank->percussion = 0;
	alBank->eadPercussion = NULL;
	alBank->countEADPercussion = 0;
	
	alBank->inst = NULL;

	if ((alBank->flags == 0x0000) || (alBank->flags == 0x0100)) // offset
	{
		alBank->inst = new ALInst*[alBank->count];

		for (int x = 0; x < alBank->count; x++)
		{
			alBank->inst[x] = new ALInst();
			alBank->inst[x]->samplerate = 0;
			alBank->inst[x]->sounds = NULL;
		}

		int x = 0;
		{
			alBank->inst[x]->soundCount = CharArrayToShort(&ctl[bankOffset-2]);
			alBank->inst[x]->sounds = new ALSound*[alBank->inst[x]->soundCount];

			for (int y = 0; y < alBank->inst[x]->soundCount; y++)
			{
				alBank->inst[x]->sounds[y] = new ALSound();
				alBank->inst[x]->sounds[y]->wav.wavData = NULL;
			}

			for (int y = 0; y < alBank->inst[x]->soundCount; y++)
			{
				unsigned long offsetSound = ctlOffset + (0x10 * y);

				alBank->inst[x]->sounds[y]->samplePan = ctl[offsetSound+0xC];
				alBank->inst[x]->sounds[y]->sampleVolume = ctl[offsetSound+0xD];
				alBank->inst[x]->sounds[y]->flags = ctl[offsetSound+0xE];

				
				if ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1))
				{
					unsigned long offsetEnv = CharArrayToLong(&ctl[offsetSound+ 0x0]);
					if (alBank->inst[x]->sounds[y]->flags == 0x1)
						offsetEnv = ctlFlaggedOffset + (offsetEnv - mask);
					else
						offsetEnv = ctlOffset + offsetEnv;

					alBank->inst[x]->samplerate = CharArrayToLong(&ctl[offsetSound+ 0x4]);

					unsigned long offsetWaveTable = CharArrayToLong(&ctl[offsetSound+ 0x8]);
					if (alBank->inst[x]->sounds[y]->flags == 0x1)
						offsetWaveTable = ctlFlaggedOffset + (offsetWaveTable - mask);
					else
						offsetWaveTable = ctlOffset + offsetWaveTable;

					alBank->inst[x]->sounds[y]->env.attackTime = CharArrayToLong(&ctl[offsetEnv + 0x0]);
					alBank->inst[x]->sounds[y]->env.decayTime = CharArrayToLong(&ctl[offsetEnv + 0x4]);
					alBank->inst[x]->sounds[y]->env.releaseTime = CharArrayToLong(&ctl[offsetEnv + 0x8]);
					alBank->inst[x]->sounds[y]->env.attackVolume = ctl[offsetEnv + 0xC];
					alBank->inst[x]->sounds[y]->env.decayVolume = ctl[offsetEnv + 0xD];
					alBank->inst[x]->sounds[y]->env.zeroPad = CharArrayToShort(&ctl[offsetEnv + 0xE]);

					unsigned char flag = CharArrayToLong(&ctl[offsetWaveTable + 0x0]) >> 24; // hack for NUD-DSCJ-JPN, can't imagine impact others
					if (flag == 0x40) // Means using 64DD IPL Bank
						alBank->inst[x]->sounds[y]->wav.base = (CharArrayToLong(&ctl[offsetWaveTable + 0x0]) & 0xFFFFFF) + 0x140000;
					else
						alBank->inst[x]->sounds[y]->wav.base = CharArrayToLong(&ctl[offsetWaveTable + 0x0]);
					alBank->inst[x]->sounds[y]->wav.len = CharArrayToLong(&ctl[offsetWaveTable + 0x4]);
					alBank->inst[x]->sounds[y]->wav.wavData = new unsigned char[alBank->inst[x]->sounds[y]->wav.len];

					for (int  r = 0; r < alBank->inst[x]->sounds[y]->wav.len; r++)
					{
						if (flag == 0x40)
						{
							alBank->inst[x]->sounds[y]->wav.wavData[r] = ROM[alBank->inst[x]->sounds[y]->wav.base + r];
						}
						else
						{
							alBank->inst[x]->sounds[y]->wav.wavData[r] = tbl[alBank->inst[x]->sounds[y]->wav.base + r];
						}
					}
					

					alBank->inst[x]->sounds[y]->wav.type = ctl[offsetWaveTable + 0x8];
					alBank->inst[x]->sounds[y]->wav.flags = ctl[offsetWaveTable + 0x9];
					// MUST PAD to 4s

					if ((alBank->inst[x]->sounds[y]->wav.type == AL_ADPCM_WAVE) && ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1)))
					{
						alBank->inst[x]->sounds[y]->wav.adpcmWave = new ALADPCMWaveInfo();
						unsigned long loopOffset = CharArrayToLong(&ctl[offsetWaveTable + 0xC]);
						unsigned long predictorOffset = CharArrayToLong(&ctl[offsetWaveTable + 0x10]);

						if (loopOffset != 0)
						{
							if (alBank->inst[x]->sounds[y]->flags == 0x1)
								loopOffset = ctlFlaggedOffset + (loopOffset - mask);
							else
								loopOffset = ctlOffset + loopOffset;

							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = new ALADPCMloop();
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);
							for (int z = 0; z < 0x10; z++)
							{
								alBank->inst[x]->sounds[y]->wav.adpcmWave->loop->state[z] = CharArrayToShort(&ctl[loopOffset + 0xC + z * 2]);
							}
						}
						else
						{
							alBank->inst[x]->sounds[y]->wav.adpcmWave->loop = NULL;
						}

						if (predictorOffset != 0)
						{
							if (alBank->inst[x]->sounds[y]->flags == 0x1)
								predictorOffset = ctlFlaggedOffset + (predictorOffset - mask);
							else
								predictorOffset = ctlOffset + predictorOffset;

							alBank->inst[x]->sounds[y]->wav.adpcmWave->book = new ALADPCMBook();
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order = CharArrayToLong(&ctl[predictorOffset + 0x0]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors = CharArrayToLong(&ctl[predictorOffset + 0x4]);
							alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors = new signed short[alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8];

							for (int z = 0; z < alBank->inst[x]->sounds[y]->wav.adpcmWave->book->order * alBank->inst[x]->sounds[y]->wav.adpcmWave->book->npredictors * 8; z++)
							{
								alBank->inst[x]->sounds[y]->wav.adpcmWave->book->predictors[z] = (signed short)CharArrayToShort(&ctl[predictorOffset + 0x8 + z * 2]);
							}
						}
					}
					else if ((alBank->inst[x]->sounds[y]->flags == 0x0) || (alBank->inst[x]->sounds[y]->flags == 0x1))
					{
						alBank->inst[x]->sounds[y]->wav.rawWave = new ALRAWWaveInfo();
						unsigned long loopOffset = CharArrayToLong(&ctl[offsetWaveTable + 0xC]);

						if (loopOffset != 0)
						{
							if (alBank->inst[x]->sounds[y]->flags == 0x1)
								loopOffset = ctlFlaggedOffset + (loopOffset - mask);
							else
								loopOffset = ctlOffset + loopOffset;

							alBank->inst[x]->sounds[y]->wav.rawWave->loop = new ALRawLoop();
							alBank->inst[x]->sounds[y]->wav.rawWave->loop->start = CharArrayToLong(&ctl[loopOffset + 0x0]);
							alBank->inst[x]->sounds[y]->wav.rawWave->loop->end = CharArrayToLong(&ctl[loopOffset + 0x4]);
							alBank->inst[x]->sounds[y]->wav.rawWave->loop->count = CharArrayToLong(&ctl[loopOffset + 0x8]);	
						}
						else
						{
							alBank->inst[x]->sounds[y]->wav.rawWave->loop = NULL;
						}
					}
					else
					{
						DisposeALBank(alBank);
						MessageBox(NULL, "Error", "Unsupported type in ALSound wav", NULL);
						return NULL;
					}
				}
				else
				{
					DisposeALBank(alBank);
					MessageBox(NULL, "Error", "Unsupported type in ALSound", NULL);
					return NULL;
				}
			}
		}
	}
	else
	{
		DisposeALBank(alBank);
		MessageBox(NULL, "Error", "Unsupported type in ALBank", NULL);
		return NULL;
	}

	return alBank;
}

int CN64AIFCAudio::GetSizeFile(CString filename)
{
	FILE* inFile = fopen(filename, "rb");
	
	if (inFile == 0)
		return 0;

	fseek(inFile, 0, SEEK_END);
	int fileSize = ftell(inFile);
	fclose(inFile);
	return fileSize;
}


unsigned short CN64AIFCAudio::Flip16Bit(unsigned short ShortValue)
{
	return ((ShortValue >> 8) | ((ShortValue << 8)));
}

unsigned long CN64AIFCAudio::Flip32Bit(unsigned long inLong)
{
	return (((inLong & 0xFF000000) >> 24) | ((inLong & 0x00FF0000) >> 8) | ((inLong & 0x0000FF00) << 8) | ((inLong & 0x000000FF) << 24));
}

unsigned short CN64AIFCAudio::CharArrayToShort(unsigned char* currentSpot)
{
	return Flip16Bit(*reinterpret_cast<unsigned short*> (currentSpot));
}

float CN64AIFCAudio::CharArrayToFloat(unsigned char* currentSpot)
{
	unsigned long tempLong = (Flip32Bit(*reinterpret_cast<unsigned long*> (currentSpot)));
	return (*reinterpret_cast<float*> (&tempLong));
}

unsigned long CN64AIFCAudio::CharArrayToLong(unsigned char* currentSpot)
{
	return Flip32Bit(*reinterpret_cast<unsigned long*> (currentSpot));
}

void CN64AIFCAudio::WriteLongToBuffer(unsigned char* Buffer, unsigned long address, unsigned long data)
{
	Buffer[address] = ((data >> 24) & 0xFF);
	Buffer[address+1] = ((data >> 16) & 0xFF);
	Buffer[address+2] = ((data >> 8) & 0xFF);
	Buffer[address+3] = ((data) & 0xFF);
}

void CN64AIFCAudio::WriteShortToBuffer(unsigned char* Buffer, unsigned long address, unsigned short data)
{
	Buffer[address] = ((data >> 8) & 0xFF);
	Buffer[address+1] = ((data) & 0xFF);	
}

int CN64AIFCAudio::ReadCtlTblLocations(unsigned char* ROM, int romSize, std::vector<ctlTblResult>& results)
{
	int numResults = 0;
	for (int x = 0x0; x < (romSize - 4); x+=4)
	{
		unsigned long value = CharArrayToLong(&ROM[x]);

 		if (value == 0x42310001)
		{
			results.resize(numResults+1);
			// possible ctl
			unsigned long bankOffset = CharArrayToLong(&ROM[x+4]);
			if ((bankOffset >> 24) != 0x80) // not pointer
				bankOffset = (x + bankOffset);
			else // absolute pointer, mask
				bankOffset = (bankOffset & 0xFFFFFF);

			if (bankOffset > romSize)
				continue;

			unsigned short numberInstruments = CharArrayToShort(&ROM[bankOffset]);

			unsigned long endInstrumentOffsets = (bankOffset + 0xC + (4 * numberInstruments));

			if (endInstrumentOffsets > romSize)
				continue;

			unsigned long tbl = endInstrumentOffsets;
			if ((endInstrumentOffsets % 0x10) != 0)
				tbl += (0x10 - (endInstrumentOffsets % 0x10));
			else
				tbl += 0x10;

			while (CharArrayToLong(&ROM[tbl]) != 0)
			{
				tbl -= 4;
			}

			tbl += 4;

			results[numResults].ctlOffset = x;
			results[numResults].tblOffset = tbl;
			results[numResults].ctlSize = (results[numResults].tblOffset - results[numResults].ctlOffset);
			if (results[numResults].tblOffset > results[numResults].ctlOffset)
				results[numResults].tblSize = (romSize - results[numResults].tblOffset);
			else
				results[numResults].tblSize = (results[numResults].ctlOffset - results[numResults].tblOffset);

			results[numResults].bank = ReadAudio(ROM, &ROM[0], results[numResults].ctlSize, results[numResults].ctlOffset, &ROM[results[numResults].tblOffset], 0, 0xFFFFFFFF, 0);

			if (results[numResults].bank != NULL)
			{
				unsigned long tblHighestSpot = 0;


				
				for (int y = 0; y < results[numResults].bank->count; y++)
				{
					for (int z = 0; z < results[numResults].bank->inst[y]->soundCount; z++)
					{
						if ((results[numResults].bank->inst[y]->sounds[z]->wav.base + results[numResults].bank->inst[y]->sounds[z]->wav.len) > tblHighestSpot)
							tblHighestSpot = (results[numResults].bank->inst[y]->sounds[z]->wav.base + results[numResults].bank->inst[y]->sounds[z]->wav.len);
					}
				}

				if ((tblHighestSpot % 0x10) != 0)
					tblHighestSpot += (0x10 - (tblHighestSpot % 0x10));

				results[numResults].tblSize = tblHighestSpot;

				numResults++;

				if (numResults == 10)
					return numResults;
			}
		}
	}
	return numResults;
}

// ***************	//
// VADPCM Decoding	//
// By Ice Mario!	//
// ***************	//

static const short itable[16] =
{
	0,1,2,3,4,5,6,7,
	-8,-7,-6,-5,-4,-3,-2,-1,
};

static const short itable_half[4] =
{
	0,1,
	-2,-1,
};

//#define ENCODE

signed short SignExtend(unsigned b, // number of bits representing the number in x
						int x      // sign extend this b-bit number to r
)
{
	

	int m = 1 << (b - 1); // mask can be pre-computed if b is fixed

	x = x & ((1 << b) - 1);  // (Skip this if bits in x above position b are already zero.)
	return (x ^ m) - m;
}

void CN64AIFCAudio::decode_8( unsigned char *in, signed short *out , int index, signed short * pred1, signed short lastsmp[8])
{
	int i;
	signed short tmp[8];
	signed long total = 0;
	signed short sample =0;
	memset(out, 0, sizeof(signed short)*8);

	signed short *pred2 = (pred1 + 8);

	//printf("pred2[] = %x\n" , pred2[0]);
	for(i=0; i<8; i++)
	{
		tmp[i] = itable[(i&1) ? (*in++ & 0xf) : ((*in >> 4) & 0xf)] << index;
		tmp[i] = SignExtend(index+4, tmp[i]);
	}

	for(i=0; i<8; i++)
	{
		total = (pred1[i] * lastsmp[6]);
		total+= (pred2[i] * lastsmp[7]);

		if (i>0)
		{
			for(int x=i-1; x>-1; x--)
			{
				total += ( tmp[((i-1)-x)] * pred2[x] );
				//printf("sample: %x - pred: %x - _smp: %x\n" , ((i-1)-x) , pred2[x] , tmp[((i-1)-x)]);
			}
		}

		//printf("pred = %x | total = %x\n" , pred2[0] , total);
		float result = ((tmp[i] << 0xb) + total) >> 0xb;
		if (result > 32767)
			sample = 32767;
		else if (result < -32768)
			sample = -32768;
		else
			sample = (signed short)result;

		out[i] = sample;
	}
	// update the last sample set for subsequent iterations
	memcpy(lastsmp, out, sizeof(signed short)*8);
}

void CN64AIFCAudio::decode_8_half( unsigned char *in, signed short *out , int index, signed short * pred1, signed short lastsmp[8])
{
	int i;
	signed short tmp[8];
	signed long total = 0;
	signed short sample =0;
	memset(out, 0, sizeof(signed short)*8);

	signed short *pred2 = (pred1 + 8);

	//printf("pred2[] = %x\n" , pred2[0]);

	tmp[0] = (((((*in) & 0xC0) >> 6) & 0x3)) << (index);
	tmp[0] = SignExtend(index+2, tmp[0]);
	tmp[1] = (((((*in) & 0x30) >> 4) & 0x3)) << (index);
	tmp[1] = SignExtend(index+2, tmp[1]);
	tmp[2] = (((((*in) & 0x0C) >> 2) & 0x3)) << (index);
	tmp[2] = SignExtend(index+2, tmp[2]);
	tmp[3] = ((((*in++) & 0x03) & 0x3)) << (index);
	tmp[3] = SignExtend(index+2, tmp[3]);
	tmp[4] = (((((*in) & 0xC0) >> 6) & 0x3)) << (index);
	tmp[4] = SignExtend(index+2, tmp[4]);
	tmp[5] = (((((*in) & 0x30) >> 4) & 0x3)) << (index);
	tmp[5] = SignExtend(index+2, tmp[5]);
	tmp[6] = (((((*in) & 0x0C) >> 2) & 0x3)) << (index);
	tmp[6] = SignExtend(index+2, tmp[6]);
	tmp[7] = ((((*in++) & 0x03) & 0x3)) << (index);
	tmp[7] = SignExtend(index+2, tmp[7]);

	for(i=0; i<8; i++)
	{
		total = (pred1[i] * lastsmp[6]);
		total+= (pred2[i] * lastsmp[7]);

		if (i>0)
		{
			for(int x=i-1; x>-1; x--)
			{
				total += ( tmp[((i-1)-x)] * pred2[x] );
				//printf("sample: %x - pred: %x - _smp: %x\n" , ((i-1)-x) , pred2[x] , tmp[((i-1)-x)]);
			}
		}

		//printf("pred = %x | total = %x\n" , pred2[0] , total);
		float result = ((tmp[i] << 0xb) + total) >> 0xb;
		if (result > 32767)
			sample = 32767;
		else if (result < -32768)
			sample = -32768;
		else
			sample = (signed short)result;

		out[i] = sample;
	}
	// update the last sample set for subsequent iterations
	memcpy(lastsmp, out, sizeof(signed short)*8);
}


signed short adpcm_get_predicted_sample(unsigned char byte, unsigned char mask,
                                          unsigned lshift, unsigned rshift)
{
    signed short sample = ((signed short)byte & (signed short)mask) << lshift;
    sample >>= rshift; /* signed */
    return sample;
}

void adpcm_get_predicted_frame(signed short *dst, unsigned char *src,
                                      unsigned char *nibbles,
                                      unsigned int rshift)
{
    unsigned int i;

    *(dst++) = (src[0] << 8) | src[1];
    *(dst++) = (src[2] << 8) | src[3];

    for (i = 1; i < 16; ++i) 
	{
        unsigned char byteData = nibbles[i];

        *(dst++) = adpcm_get_predicted_sample(byteData, 0xf0,  8, rshift);
        *(dst++) = adpcm_get_predicted_sample(byteData, 0x0f, 12, rshift);
    }
}

signed short clamp_s16(int x)
{
    x = (x < (-0x7fff - 1)) ? (-0x7fff - 1): x;
    x = (x > 0x7fff) ? 0x7fff: x;

    return x;
}

int rdot(unsigned int n, const signed short *x, signed short *y)
{
    int accu = 0;

    y += n;

    while (n != 0) {
        accu += ((int)*(x++) * (int)*(--y));
        --n;
    }

    return accu;
}

void adpcm_decode_upto_8_samples(signed short *dst, signed short *src,
                                        signed short *cb_entry,
                                        signed short *last_samples,
                                        unsigned int size)
{
    signed short * book1 = cb_entry;
    signed short * book2 = cb_entry + 8;

    signed short l1 = last_samples[0];
    signed short l2 = last_samples[1];

    unsigned int i;
    int accu;

    for (i = 0; i < size; ++i) {
        accu = (int)src[i] << 11;
        accu += book1[i] * l1 + book2[i] * l2 + rdot(i, book2, src);
        dst[i] = clamp_s16(accu >> 11);
    }
}

unsigned long CN64AIFCAudio::decodemusyxadpcm( unsigned char *in, signed short *out, unsigned long len, ALADPCMBook *book )
{
	signed short frame[32];

	int samples = 0;
 
    for (unsigned int i = 0; i < len; i+=0x28)
	{
		// TODO process the small missing end if figure out how
		if ((len - i) < 0x28)
		{
			return samples;	
		}

        unsigned char c2 = in[i+0x8];

		signed short* bookPredictors = (c2 & 0xf0) + book->predictors;
        unsigned int rshift = (c2 & 0x0f);

        adpcm_get_predicted_frame(frame, &in[i], &in[i+0x8], rshift);

        memcpy(out, frame, 2 * sizeof(frame[0]));
        adpcm_decode_upto_8_samples(out +  2, frame +  2, bookPredictors, out     , 6);
        adpcm_decode_upto_8_samples(out +  8, frame +  8, bookPredictors, out +  6, 8);
        adpcm_decode_upto_8_samples(out + 16, frame + 16, bookPredictors, out + 14, 8);
        adpcm_decode_upto_8_samples(out + 24, frame + 24, bookPredictors, out + 22, 8);

		out += 32;
		samples += 32;

		c2 = in[i+0x18];

        bookPredictors = (c2 & 0xf0) + book->predictors;
        rshift = (c2 & 0x0f);

        adpcm_get_predicted_frame(frame, &in[i+4], &in[i+0x18], rshift);

        memcpy(out, frame, 2 * sizeof(frame[0]));
        adpcm_decode_upto_8_samples(out +  2, frame +  2, bookPredictors, out     , 6);
        adpcm_decode_upto_8_samples(out +  8, frame +  8, bookPredictors, out +  6, 8);
        adpcm_decode_upto_8_samples(out + 16, frame + 16, bookPredictors, out + 14, 8);
        adpcm_decode_upto_8_samples(out + 24, frame + 24, bookPredictors, out + 22, 8);

		out += 32;
		samples += 32;
    }

	return samples;
}

unsigned long CN64AIFCAudio::decode( unsigned char *in, signed short *out, unsigned long len, ALADPCMBook *book, bool decode8Only )
{
	signed short lastsmp[8];

	for (int x = 0; x < 8; x++)
		lastsmp[x] = 0;

	int index;
	int pred;
	unsigned char cmd;
	unsigned char *pin = in;
	signed short *pout = out;
	int j;
	unsigned char n1,n2;
	int total = 0;
	int _tmp;

	int samples = 0;

	// flip the predictors
	signed short *preds = (signed short*)malloc( 32 * book->npredictors );
	for(int p=0; p<(16*book->npredictors); p++)
	{
		preds[p] = book->predictors[p];
	}

	if (!decode8Only)
	{
		int _len = (len / 9) * 9;	//make sure length was actually a multiple of 9

		while(_len > 0)
		{
			index = (*in >> 4) & 0xf;
			pred = (*in & 0xf);

			// to not make zelda crash but doesn't fix it
			if (pred >= (book->npredictors * book->order))
				pred -= (book->npredictors * book->order);
			_len--;

			signed short * pred1 = &preds[ pred * 16] ;

			decode_8(++in, out, index, pred1, lastsmp);
			in+=4;	_len-=4;	out+=8;

			decode_8(in, out, index, pred1, lastsmp);
			in+=4;	_len-=4;	out+=8;

			samples += 16;
		}
	}
	else
	{
		int _len = (len / 5) * 5;	//make sure length was actually a multiple of 5

		while(_len > 0)
		{
			index = (*in >> 4) & 0xf;
			pred = (*in & 0xf);

			// to not make zelda crash but doesn't fix it
			if (pred >= (book->npredictors * book->order))
				pred -= (book->npredictors * book->order);
			_len--;

			signed short * pred1 = &preds[ pred * 16] ;

			decode_8_half(++in, out, index, pred1, lastsmp);
			in+=2;	_len-=2;	out+=8;

			decode_8_half(in, out, index, pred1, lastsmp);
			in+=2;	_len-=2;	out+=8;

			samples += 16;
		}
	}

	free(preds);

	return samples;
}

int CN64AIFCAudio::determineBestEncodeIndexAndPredictor_half(signed short* predictors, int numPredictors, signed short* lastSampleSet, signed short* inPCMSamples, float& bestFitIndex, int& predictorIndex)
{
        predictorIndex = 0;
        float bestPredIndex = 99999999999.0f;
 
        int bestEncodeIndex = 0;
       
        for(int p = 0; p < numPredictors; p++)
        {
                signed short* tempSampleSet = new signed short[8];
                signed short* tmp = new signed short[8];
 
                int index = 0;
                bestFitIndex = 99999999999.0f;
 
                signed short* pred1 = &predictors[p*0x10 + 0];
                signed short* pred2 = &predictors[p*0x10 + 8];
 
                for (int testIndex = 0; testIndex < 16; testIndex++)
                {
                        for (int x = 0; x < 8; x++)
                        {
                                tempSampleSet[x] = lastSampleSet[x];
                        }
 
                        float tempFitIndex = 0;
                        for (int r = 0; r < 2; r++)
                        {
                                for (int i = 0; i < 8; i++)
                                {
                                        signed short sample = inPCMSamples[(r*8)+i];
 
                                        signed long total = pred1[i] * tempSampleSet[6];
                                        total += (pred2[i] * tempSampleSet[7]);
 
                                        if (i>0)
                                        {
                                                for(int x=i-1; x>-1; x--)
                                                {
                                                        total += ( tmp[((i-1)-x)] * pred2[x] );
                                                }
                                        }
 
                                        float bestFit = 9999999999;
                                        int bestMatch = 0;
 
                                        for (int x = 0; x < 4; x++)
                                        {
                                                signed short tmpValue = (itable_half[x] << testIndex);
                                                float newValue = (((tmpValue << 0xB) + total) >> 0xB);
                                                if ((fabs((float)(sample - newValue))) < bestFit)
                                                {
                                                        bestFit = (fabs((float)(sample - newValue)));
                                                        bestMatch = x;
                                                }
                                        }
 
                                        tmp[i] = (itable_half[bestMatch] << testIndex);
                                        tempFitIndex += bestFit;
                                }
 
                       
                                for (int x = 0; x < 8; x++)
                                {
                                        tempSampleSet[x] = inPCMSamples[(r*8)+x];
                                }
                        }
 
                        if (tempFitIndex < bestFitIndex)
                        {
                                bestFitIndex = tempFitIndex;
                                index = testIndex;
                        }
                }
 
                if (bestFitIndex < bestPredIndex)
                {
                        bestPredIndex = bestFitIndex;
                        predictorIndex = p;
                        bestEncodeIndex = index;
                }
               
                delete [] tmp;
                delete [] tempSampleSet;
        }
 
        return bestEncodeIndex;
}

int CN64AIFCAudio::determineBestEncodeIndexAndPredictor(signed short* predictors, int numPredictors, signed short* lastSampleSet, signed short* inPCMSamples, float& bestFitIndex, int& predictorIndex)
{
        predictorIndex = 0;
        float bestPredIndex = 99999999999.0f;
 
        int bestEncodeIndex = 0;
       
        for(int p = 0; p < numPredictors; p++)
        {
                signed short* tempSampleSet = new signed short[8];
                signed short* tmp = new signed short[8];
 
                int index = 0;
                bestFitIndex = 99999999999.0f;
 
                signed short* pred1 = &predictors[p*0x10 + 0];
                signed short* pred2 = &predictors[p*0x10 + 8];
 
                for (int testIndex = 0; testIndex < 16; testIndex++)
                {
                        for (int x = 0; x < 8; x++)
                        {
                                tempSampleSet[x] = lastSampleSet[x];
                        }
 
                        float tempFitIndex = 0;
                        for (int r = 0; r < 2; r++)
                        {
                                for (int i = 0; i < 8; i++)
                                {
                                        signed short sample = inPCMSamples[(r*8)+i];
 
                                        signed long total = pred1[i] * tempSampleSet[6];
                                        total += (pred2[i] * tempSampleSet[7]);
 
                                        if (i>0)
                                        {
                                                for(int x=i-1; x>-1; x--)
                                                {
                                                        total += ( tmp[((i-1)-x)] * pred2[x] );
                                                }
                                        }
 
                                        float bestFit = 9999999999;
                                        int bestMatch = 0;
 
                                        for (int x = 0; x < 16; x++)
                                        {
                                                signed short tmpValue = (itable[x] << testIndex);
                                                float newValue = (((tmpValue << 0xB) + total) >> 0xB);
                                                if ((fabs((float)(sample - newValue))) < bestFit)
                                                {
                                                        bestFit = (fabs((float)(sample - newValue)));
                                                        bestMatch = x;
                                                }
                                        }
 
                                        tmp[i] = (itable[bestMatch] << testIndex);
                                        tempFitIndex += bestFit;
                                }
 
                       
                                for (int x = 0; x < 8; x++)
                                {
                                        tempSampleSet[x] = inPCMSamples[(r*8)+x];
                                }
                        }
 
                        if (tempFitIndex < bestFitIndex)
                        {
                                bestFitIndex = tempFitIndex;
                                index = testIndex;
                        }
                }
 
                if (bestFitIndex < bestPredIndex)
                {
                        bestPredIndex = bestFitIndex;
                        predictorIndex = p;
                        bestEncodeIndex = index;
                }
               
                delete [] tmp;
                delete [] tempSampleSet;
        }
 
        return bestEncodeIndex;
}

signed short* CN64AIFCAudio::determineBestPredictors(ALBank* alBank, unsigned long& npredictors, unsigned long& norder, signed short* inPCMSamples, int numberSamplesIn)
{
	int numPredTests = 0xC;
	
	signed short** predictors = new signed short*[numPredTests];
	float* entropySet = new float[numPredTests];

	for (int x = 0; x < numPredTests; x++)
	{
		predictors[x] = new signed short[0x10];
		entropySet[x] = 0;
	}

	int predNum = 0;

	// todo find some way to calculate this
	predictors[predNum][0] = 0xFAE2;
	predictors[predNum][1] = 0xFAD0;
	predictors[predNum][2] = 0xFE04;
	predictors[predNum][3] = 0x014F;
	predictors[predNum][4] = 0x0298;
	predictors[predNum][5] = 0x01CB;
	predictors[predNum][6] = 0x0029;
	predictors[predNum][7] = 0xFF03;
	predictors[predNum][8] = 0x081C;
	predictors[predNum][9] = 0x031A;
	predictors[predNum][10] = 0xFDF5;
	predictors[predNum][11] = 0xFBF2;
	predictors[predNum][12] = 0xFD32;
	predictors[predNum][13] = 0xFFC1;
	predictors[predNum][14] = 0x018B;
	predictors[predNum][15] = 0x01B9;

	unsigned long vadpcmOutputLength;
	unsigned char* vadpcmData = new unsigned char[numberSamplesIn];

	ALADPCMBook book;
	book.npredictors = 1;
	book.order = 2;
	book.predictors = predictors[predNum];
	entropySet[predNum] = encode(inPCMSamples, numberSamplesIn, vadpcmData, vadpcmOutputLength, &book);

	delete [] vadpcmData;
	predNum++;




	predictors[predNum][0] = 0xF8A1;
	predictors[predNum][1] = 0xF25D;
	predictors[predNum][2] = 0xED92;
	predictors[predNum][3] = 0xEA7A;
	predictors[predNum][4] = 0xE92C;
	predictors[predNum][5] = 0xE99D;
	predictors[predNum][6] = 0xEBA1;
	predictors[predNum][7] = 0xEEF3;
	predictors[predNum][8] = 0x0ECC;
	predictors[predNum][9] = 0x1400;
	predictors[predNum][10] = 0x175B;
	predictors[predNum][11] = 0x18C5;
	predictors[predNum][12] = 0x184B;
	predictors[predNum][13] = 0x161B;
	predictors[predNum][14] = 0x1280;
	predictors[predNum][15] = 0x0DDA;

	vadpcmData = new unsigned char[numberSamplesIn];

	book.npredictors = 1;
	book.order = 2;
	book.predictors = predictors[predNum];
	entropySet[predNum] = encode(inPCMSamples, numberSamplesIn, vadpcmData, vadpcmOutputLength, &book);

	delete [] vadpcmData;
	predNum++;


	predictors[predNum][0] = 0xFD78;
	predictors[predNum][1] = 0xFF80;
	predictors[predNum][2] = 0x00B4;
	predictors[predNum][3] = 0x004C;
	predictors[predNum][4] = 0xFFD6;
	predictors[predNum][5] = 0xFFE0;
	predictors[predNum][6] = 0x0007;
	predictors[predNum][7] = 0x000C;
	predictors[predNum][8] = 0x0194;
	predictors[predNum][9] = 0xFDC8;
	predictors[predNum][10] = 0xFF10;
	predictors[predNum][11] = 0x0085;
	predictors[predNum][12] = 0x0066;
	predictors[predNum][13] = 0xFFEA;
	predictors[predNum][14] = 0xFFDB;
	predictors[predNum][15] = 0x0000;

	vadpcmData = new unsigned char[numberSamplesIn];

	book.npredictors = 1;
	book.order = 2;
	book.predictors = predictors[predNum];
	entropySet[predNum] = encode(inPCMSamples, numberSamplesIn, vadpcmData, vadpcmOutputLength, &book);

	delete [] vadpcmData;
	predNum++;


	predictors[predNum][0] = 0x0210;
	predictors[predNum][1] = 0x00FD;
	predictors[predNum][2] = 0x0101;
	predictors[predNum][3] = 0x00BC;
	predictors[predNum][4] = 0x009C;
	predictors[predNum][5] = 0x007B;
	predictors[predNum][6] = 0x0063;
	predictors[predNum][7] = 0x004F;
	predictors[predNum][8] = 0x03D4;
	predictors[predNum][9] = 0x03E5;
	predictors[predNum][10] = 0x02D9;
	predictors[predNum][11] = 0x025E;
	predictors[predNum][12] = 0x01DE;
	predictors[predNum][13] = 0x0181;
	predictors[predNum][14] = 0x0133;
	predictors[predNum][15] = 0x00F6;

	vadpcmData = new unsigned char[numberSamplesIn];

	book.npredictors = 1;
	book.order = 2;
	book.predictors = predictors[predNum];
	entropySet[predNum] = encode(inPCMSamples, numberSamplesIn, vadpcmData, vadpcmOutputLength, &book);

	delete [] vadpcmData;
	predNum++;


	predictors[predNum][0] = 0x01CF;
	predictors[predNum][1] = 0x003E;
	predictors[predNum][2] = 0x0071;
	predictors[predNum][3] = 0x001D;
	predictors[predNum][4] = 0x001D;
	predictors[predNum][5] = 0x000B;
	predictors[predNum][6] = 0x0008;
	predictors[predNum][7] = 0x0003;
	predictors[predNum][8] = 0x0112;
	predictors[predNum][9] = 0x01F4;
	predictors[predNum][10] = 0x0081;
	predictors[predNum][11] = 0x0082;
	predictors[predNum][12] = 0x002F;
	predictors[predNum][13] = 0x0024;
	predictors[predNum][14] = 0x000F;
	predictors[predNum][15] = 0x000A;

	vadpcmData = new unsigned char[numberSamplesIn];

	book.npredictors = 1;
	book.order = 2;
	book.predictors = predictors[predNum];
	entropySet[predNum] = encode(inPCMSamples, numberSamplesIn, vadpcmData, vadpcmOutputLength, &book);

	delete [] vadpcmData;
	predNum++;

	predictors[predNum][0] = 0xFCC0;
	predictors[predNum][1] = 0xFBEC;
	predictors[predNum][2] = 0xFC33;
	predictors[predNum][3] = 0xFCE2;
	predictors[predNum][4] = 0xFDA2;
	predictors[predNum][5] = 0xFE4B;
	predictors[predNum][6] = 0xFED1;
	predictors[predNum][7] = 0xFF36;
	predictors[predNum][8] = 0x0A0B;
	predictors[predNum][9] = 0x095C;
	predictors[predNum][10] = 0x07AC;
	predictors[predNum][11] = 0x05D5;
	predictors[predNum][12] = 0x0435;
	predictors[predNum][13] = 0x02E9;
	predictors[predNum][14] = 0x01F2;
	predictors[predNum][15] = 0x0143;

	vadpcmData = new unsigned char[numberSamplesIn];

	book.npredictors = 1;
	book.order = 2;
	book.predictors = predictors[predNum];
	entropySet[predNum] = encode(inPCMSamples, numberSamplesIn, vadpcmData, vadpcmOutputLength, &book);

	delete [] vadpcmData;
	predNum++;

	predictors[predNum][0] = 0xFBF6;
	predictors[predNum][1] = 0xFBDF;
	predictors[predNum][2] = 0xFDD1;
	predictors[predNum][3] = 0xFFDA;
	predictors[predNum][4] = 0x00F4;
	predictors[predNum][5] = 0x010C;
	predictors[predNum][6] = 0x0097;
	predictors[predNum][7] = 0x0013;
	predictors[predNum][8] = 0x082E;
	predictors[predNum][9] = 0x0453;
	predictors[predNum][10] = 0x004B;
	predictors[predNum][11] = 0xFE1D;
	predictors[predNum][12] = 0xFDED;
	predictors[predNum][13] = 0xFED4;
	predictors[predNum][14] = 0xFFDA;
	predictors[predNum][15] = 0x0070;

	vadpcmData = new unsigned char[numberSamplesIn];

	book.npredictors = 1;
	book.order = 2;
	book.predictors = predictors[predNum];
	entropySet[predNum] = encode(inPCMSamples, numberSamplesIn, vadpcmData, vadpcmOutputLength, &book);

	delete [] vadpcmData;
	predNum++;

	predictors[predNum][0] = 0xFB63;
	predictors[predNum][1] = 0xF930;
	predictors[predNum][2] = 0xF89A;
	predictors[predNum][3] = 0xF901;
	predictors[predNum][4] = 0xF9F0;
	predictors[predNum][5] = 0xFB15;
	predictors[predNum][6] = 0xFC3C;
	predictors[predNum][7] = 0xFD46;
	predictors[predNum][8] = 0x0BD0;
	predictors[predNum][9] = 0x0CD4;
	predictors[predNum][10] = 0x0C21;
	predictors[predNum][11] = 0x0A84;
	predictors[predNum][12] = 0x0888;
	predictors[predNum][13] = 0x0688;
	predictors[predNum][14] = 0x04BA;
	predictors[predNum][15] = 0x0336;

	vadpcmData = new unsigned char[numberSamplesIn];

	book.npredictors = 1;
	book.order = 2;
	book.predictors = predictors[predNum];
	entropySet[predNum] = encode(inPCMSamples, numberSamplesIn, vadpcmData, vadpcmOutputLength, &book);

	delete [] vadpcmData;
	predNum++;

	predictors[predNum][0] = 0xF9D0;
	predictors[predNum][1] = 0xF692;
	predictors[predNum][2] = 0xF66C;
	predictors[predNum][3] = 0xF8B4;
	predictors[predNum][4] = 0xFC4A;
	predictors[predNum][5] = 0xFFFF;
	predictors[predNum][6] = 0x02DD;
	predictors[predNum][7] = 0x045D;
	predictors[predNum][8] = 0x0C30;
	predictors[predNum][9] = 0x0C62;
	predictors[predNum][10] = 0x096F;
	predictors[predNum][11] = 0x04CB;
	predictors[predNum][12] = 0x0002;
	predictors[predNum][13] = 0xFC4D;
	predictors[predNum][14] = 0xFA5C;
	predictors[predNum][15] = 0xFA44;

	vadpcmData = new unsigned char[numberSamplesIn];

	book.npredictors = 1;
	book.order = 2;
	book.predictors = predictors[predNum];
	entropySet[predNum] = encode(inPCMSamples, numberSamplesIn, vadpcmData, vadpcmOutputLength, &book);

	delete [] vadpcmData;
	predNum++;

	predictors[predNum][0] = 0x0000;
	predictors[predNum][1] = 0x0000;
	predictors[predNum][2] = 0x0000;
	predictors[predNum][3] = 0x0000;
	predictors[predNum][4] = 0x0000;
	predictors[predNum][5] = 0x0000;
	predictors[predNum][6] = 0x0000;
	predictors[predNum][7] = 0x0000;
	predictors[predNum][8] = 0x0000;
	predictors[predNum][9] = 0x0000;
	predictors[predNum][10] = 0x0000;
	predictors[predNum][11] = 0x0000;
	predictors[predNum][12] = 0x0000;
	predictors[predNum][13] = 0x0000;
	predictors[predNum][14] = 0x0000;
	predictors[predNum][15] = 0x0000;

	vadpcmData = new unsigned char[numberSamplesIn];

	book.npredictors = 1;
	book.order = 2;
	book.predictors = predictors[predNum];
	entropySet[predNum] = encode(inPCMSamples, numberSamplesIn, vadpcmData, vadpcmOutputLength, &book);

	delete [] vadpcmData;
	predNum++;

	predictors[predNum][0] = 0xFA92;
	predictors[predNum][1] = 0xF99C;
	predictors[predNum][2] = 0xFC2B;
	predictors[predNum][3] = 0xFFD4;
	predictors[predNum][4] = 0x0266;
	predictors[predNum][5] = 0x02F0;
	predictors[predNum][6] = 0x01D5;
	predictors[predNum][7] = 0x0029;
	predictors[predNum][8] = 0x096A;
	predictors[predNum][9] = 0x05A5;
	predictors[predNum][10] = 0x0041;
	predictors[predNum][11] = 0xFC77;
	predictors[predNum][12] = 0xFBAB;
	predictors[predNum][13] = 0xFD4E;
	predictors[predNum][14] = 0xFFC4;
	predictors[predNum][15] = 0x018E;

	vadpcmData = new unsigned char[numberSamplesIn];

	book.npredictors = 1;
	book.order = 2;
	book.predictors = predictors[predNum];
	entropySet[predNum] = encode(inPCMSamples, numberSamplesIn, vadpcmData, vadpcmOutputLength, &book);

	delete [] vadpcmData;
	predNum++;

	predictors[predNum][0] = 0xFB0A;
	predictors[predNum][1] = 0xF88C;
	predictors[predNum][2] = 0xF7E3;
	predictors[predNum][3] = 0xF870;
	predictors[predNum][4] = 0xF9AD;
	predictors[predNum][5] = 0xFB31;
	predictors[predNum][6] = 0xFCB4;
	predictors[predNum][7] = 0xFE07;
	predictors[predNum][8] = 0x0C04;
	predictors[predNum][9] = 0x0D15;
	predictors[predNum][10] = 0x0C32;
	predictors[predNum][11] = 0x0A33;
	predictors[predNum][12] = 0x07C1;
	predictors[predNum][13] = 0x0551;
	predictors[predNum][14] = 0x032D;
	predictors[predNum][15] = 0x0179;

	vadpcmData = new unsigned char[numberSamplesIn];

	book.npredictors = 1;
	book.order = 2;
	book.predictors = predictors[predNum];
	entropySet[predNum] = encode(inPCMSamples, numberSamplesIn, vadpcmData, vadpcmOutputLength, &book);

	delete [] vadpcmData;
	predNum++;

	int numFinalPred = 4;
	npredictors = numFinalPred;
	norder = 2;

	selectionSortAscending(entropySet, predictors, numPredTests);

	

	signed short* finalPred = new signed short[numFinalPred * 0x10];
	for (int x = 0; x < numFinalPred; x++)
	{
		for (int y = 0; y < 0x10; y++)
		{
			finalPred[x*0x10+y] = predictors[x][y];
		}
	}

	for (int x = 0; x < numPredTests; x++)
	{
		delete [] predictors[x];
	}

	delete [] predictors;
	delete [] entropySet;

	/*FILE* inFile2 = fopen("C:\\temp\\predictorset.bin", "rb");
	fseek(inFile2, 0, SEEK_END);
	int size = ftell(inFile2);
	fseek(inFile2, 0, SEEK_SET);
	unsigned char* buffer2 = new unsigned char[size];
	fread(buffer2, 1, (size), inFile2);
	fclose(inFile2);

	float bestEntropy = 99999999999.0f;
	unsigned long bestPredOffset = 0;

	for (unsigned long x = 0; x < size; x += 0x20)
	{
		signed short* predictors = new signed short[0x10];
		for (int r = 0; r < 0x10; r++)
		{
			predictors[r] = (signed short)((buffer2[x+r*2+0] << 8) | buffer2[x+r*2+1]);
		}

		unsigned long vadpcmOutputLength;
		unsigned char* vadpcmData = new unsigned char[numberSamplesIn];

		ALADPCMBook book;
		book.npredictors = 1;
		book.order = 2;
		book.predictors = predictors;
		float entropy = encode(inPCMSamples, numberSamplesIn, vadpcmData, vadpcmOutputLength, &book);

		if (entropy < bestEntropy)
		{
			bestPredOffset = x;
			bestEntropy = entropy;
		}

		delete [] vadpcmData;
		delete [] predictors;
	}
	
	delete [] buffer2;

	signed short* finalPred = new signed short[0x10];
	for (int x = 0; x < 0x10; x++)
	{
		finalPred[x] = (signed short)((buffer2[bestPredOffset + x*2+0] << 8) | buffer2[bestPredOffset + x*2+1]);
	}*/

	return finalPred;
}

void CN64AIFCAudio::selectionSortAscending(float *array, signed short** arrayCopy, int length)
{
	int i,j,minat;
	float min;
	for(i=0;i<(length-1);i++)
	{
		minat=i;
		min=array[i];

		for(j=i+1;j<(length);j++) //select the min of the rest of array
		{
			if(min>array[j])   //ascending order for descending reverse
			{
				minat=j;  //the position of the min element 
				min=array[j];
			}
		}
		float temp=array[i] ;
		array[i]=array[minat];  //swap 
		array[minat]=temp;

		signed short tempArrayCopy[0x10];
		for (int r = 0; r < 0x10; r++)
		{
			tempArrayCopy[r] = arrayCopy[i][r];
			arrayCopy[i][r] = arrayCopy[minat][r];
			arrayCopy[minat][r] = tempArrayCopy[r];
		}
	}
}

int CN64AIFCAudio::determineBestEncodeIndex(signed short* pred1, signed short* pred2, signed short* lastSampleSet, signed short* inPCMSamples, float& bestFitIndex)
{
	signed short* tempSampleSet = new signed short[8];
	signed short* tmp = new signed short[8];

	int index = 0;
	bestFitIndex = 99999999999.0f;

	for (int testIndex = 0; testIndex < 16; testIndex++)
	{
		for (int x = 0; x < 8; x++)
		{
			tempSampleSet[x] = lastSampleSet[x];
		}

		float tempFitIndex = 0;
		for (int r = 0; r < 2; r++)
		{
			for (int i = 0; i < 8; i++)
			{
				signed short sample = inPCMSamples[(r*8)+i];

				signed long total = pred1[i] * tempSampleSet[6];
				total += (pred2[i] * tempSampleSet[7]);

				if (i>0)
				{
					for(int x=i-1; x>-1; x--)
					{
						total += ( tmp[((i-1)-x)] * pred2[x] );
					}
				}

				float bestFit = 9999999999;
				int bestMatch = 0;

				for (int x = 0; x < 16; x++)
				{
					signed short newValue = ((((itable[x] << testIndex) << 0xB) + total) >> 0xB);
					if ((fabs((float)(sample - newValue))) < bestFit)
					{
						bestFit = (fabs((float)(sample - newValue)));
						bestMatch = x;
					}
				}

				tmp[i] = (itable[bestMatch] << testIndex);
				tempFitIndex += bestFit;
			}

			
			for (int x = 0; x < 8; x++)
			{
				tempSampleSet[x] = inPCMSamples[(r*8)+x];
			}
		}

		if (tempFitIndex < bestFitIndex)
		{
			bestFitIndex = tempFitIndex;
			index = testIndex;
		}
	}

	delete [] tmp;
	delete [] tempSampleSet;

	return index;
}

float CN64AIFCAudio::encode_half(signed short* inPCMSamples, int numberSamplesIn, unsigned char* outVADPCM, unsigned long& lenOut, ALADPCMBook *book)
{
	float entropy = 0.0f;

	signed short* lastSampleSet = new signed short[8];
	for (int x = 0; x < 8; x++)
		lastSampleSet[x] = 0x0;

	signed short* tmp = new signed short[8];

	lenOut = 0;

	for (int y = 0; y < numberSamplesIn; y += 16)
	{
		float totalBestFitDelta = 0;

		signed short* pred1;
		signed short* pred2;

		int predictor = 0;
		int index = 0;

		index = determineBestEncodeIndexAndPredictor_half(book->predictors, book->npredictors, lastSampleSet, &inPCMSamples[y], totalBestFitDelta, predictor);

		pred1 = &book->predictors[predictor*0x10 + 0];
		pred2 = &book->predictors[predictor*0x10 + 8];

		outVADPCM[lenOut++] = ((index << 4) | predictor);

		for (int r = 0; r < 2; r++)
		{
			signed short resultingValue[8];
			for (int i = 0; i < 8; i++)
			{
				signed short sample = 0;
				if ((y + (r * 8) + i) < numberSamplesIn)
                {
					sample = inPCMSamples[y+(r*8)+i];
				}

				signed long total = pred1[i] * lastSampleSet[6];
				total += (pred2[i] * lastSampleSet[7]);

				if (i>0)
				{
					for(int x=i-1; x>-1; x--)
					{
						total += ( tmp[((i-1)-x)] * pred2[x] );
					}
				}

				float bestFit = 9999999999;
				int bestMatch = 0;
				

				for (int x = 0; x < 4; x++)
				{
					signed short newValue = ((((itable_half[x] << index) << 0xB) + total) >> 0xB);
					if ((fabs((float)(sample - newValue))) < bestFit)
					{
						bestFit = (fabs((float)(sample - newValue)));
						bestMatch = x;
						resultingValue[i] = newValue;
					}
				}

				tmp[i] = (itable_half[bestMatch] << index);

				if ((i % 4) == 0)
					outVADPCM[lenOut] = ((bestMatch << 6) & 0xC0);
				else if ((i % 4) == 1)
					outVADPCM[lenOut] |= ((bestMatch << 4) & 0x30);
				else if ((i % 4) == 2)
					outVADPCM[lenOut] |= ((bestMatch << 2) & 0x0C);
				else
				{
					outVADPCM[lenOut] = (outVADPCM[lenOut] | (bestMatch & 0x3));
					lenOut++;
				}

				entropy += bestFit;
			}

			for (int x = 0; x < 8; x++)
			{
				//lastSampleSet[x] = inPCMSamples[y+(r*8)+x];
				lastSampleSet[x] = resultingValue[x];
			}
		}
	}


	if ((numberSamplesIn % 16) != 0)
	{
		// just cut it off for now
	}

	delete [] lastSampleSet;
	delete [] tmp;

	return entropy;
}

float CN64AIFCAudio::encode(signed short* inPCMSamples, int numberSamplesIn, unsigned char* outVADPCM, unsigned long& lenOut, ALADPCMBook *book)
{
	float entropy = 0.0f;

	signed short* lastSampleSet = new signed short[8];
	for (int x = 0; x < 8; x++)
		lastSampleSet[x] = 0x0;

	signed short* tmp = new signed short[8];

	lenOut = 0;

	for (int y = 0; y < numberSamplesIn; y += 16)
	{
		float totalBestFitDelta = 0;

		signed short* pred1;
		signed short* pred2;

		int predictor = 0;
		int index = 0;

		index = determineBestEncodeIndexAndPredictor(book->predictors, book->npredictors, lastSampleSet, &inPCMSamples[y], totalBestFitDelta, predictor);

		pred1 = &book->predictors[predictor*0x10 + 0];
		pred2 = &book->predictors[predictor*0x10 + 8];

		//index = determineBestEncodeIndex(pred1, pred2, lastSampleSet, &inPCMSamples[y], totalBestFitDelta);

		outVADPCM[lenOut++] = ((index << 4) | predictor);

		for (int r = 0; r < 2; r++)
		{
			signed short resultingValue[8];
			for (int i = 0; i < 8; i++)
			{
				signed short sample = 0;
				if ((y + (r * 8) + i) < numberSamplesIn)
                {
					sample = inPCMSamples[y+(r*8)+i];
				}

				signed long total = pred1[i] * lastSampleSet[6];
				total += (pred2[i] * lastSampleSet[7]);

				if (i>0)
				{
					for(int x=i-1; x>-1; x--)
					{
						total += ( tmp[((i-1)-x)] * pred2[x] );
					}
				}

				float bestFit = 9999999999;
				int bestMatch = 0;
				

				for (int x = 0; x < 16; x++)
				{
					signed short newValue = ((((itable[x] << index) << 0xB) + total) >> 0xB);
					if ((fabs((float)(sample - newValue))) < bestFit)
					{
						bestFit = (fabs((float)(sample - newValue)));
						bestMatch = x;
						resultingValue[i] = newValue;
					}
				}

				tmp[i] = (itable[bestMatch] << index);

				if ((i % 2) == 0)
					outVADPCM[lenOut] = (bestMatch << 4);
				else
				{
					outVADPCM[lenOut] = (outVADPCM[lenOut] | bestMatch);
					lenOut++;
				}

				entropy += bestFit;
			}

			for (int x = 0; x < 8; x++)
			{
				//lastSampleSet[x] = inPCMSamples[y+(r*8)+x];
				lastSampleSet[x] = resultingValue[x];
			}
		}
	}


	if ((numberSamplesIn % 16) != 0)
	{
		// just cut it off for now
	}

	delete [] lastSampleSet;
	delete [] tmp;

	return entropy;
}


void CN64AIFCAudio::InitializeKeyTable()
{
	//FILE* outKeyMapping = fopen("C:\\temp\\keymapping.txt", "w");
	for (int x = 0; x < 0xFF; x++)
	{
		CN64AIFCAudio::keyTable[x] = pow(2, (float)((60.0 - (float)x) / 12.0));

		//fprintf(outKeyMapping, "%02X (%d) : %f (%08X)\n", x, x, CN64AIFCAudio::keyTable[x], *reinterpret_cast<unsigned long*> (&CN64AIFCAudio::keyTable[x]));
	}
	//fclose(outKeyMapping);
}