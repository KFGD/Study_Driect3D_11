#include <iostream>
#include <Windows.h>
#include <xaudio2.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <Mferror.h>

#pragma comment (lib, "xaudio2.lib")
#pragma comment (lib, "mf.lib")
#pragma comment (lib, "mfplat.lib")
#pragma comment (lib, "mfreadwrite.lib")
#pragma comment (lib, "mfuuid.lib")

IXAudio2MasteringVoice* masteringVoice;

IMFSourceReader* pReader = nullptr;
IXAudio2SourceVoice* sourceVoice;

//Homework
//IMFSourceReader* pReader2 = nullptr;
//IXAudio2SourceVoice* sourceVoice2;

class MyVoiceCallBack;
void SubmitBuffer(MyVoiceCallBack* callback);

class MyVoiceCallBack : public IXAudio2VoiceCallback
{
public:
	bool isLast;
	unsigned sampleIndex;

public:
	MyVoiceCallBack() : isLast(false), sampleIndex(0){}

public:
	void OnVoiceProcessingPassStart(UINT32 ByteRequired){}
	void OnVoiceProcessingPassEnd(){}
	void OnStreamEnd(){}
	void OnBufferStart(void* pBufferContext){}
	void OnBufferEnd(void* pBufferContext)
	{
		SubmitBuffer(this);
	}
	void OnLoopEnd(void* pBufferContext){}
	void OnVoiceError(void* pBufferContext, HRESULT Error){}
};

int main(int argc, char** argv)
{
	if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)))
		return -1;

	if (FAILED(MFStartup(MF_VERSION)))
		return -1;

	//Homework
	if (FAILED(MFCreateSourceReaderFromURL(L"Test.mp3", nullptr, &pReader)) 
		//|| FAILED(MFCreateSourceReaderFromURL(L"Test2.mp3", nullptr, &pReader2))
		)
	{
		MFShutdown();
		CoUninitialize();
		return -1;
	}

	IXAudio2* xaudio2;
	if (FAILED(XAudio2Create(&xaudio2)))
	{
		pReader->Release();
		//pReader2->Release();	//Homework
		MFShutdown();
		CoUninitialize();
		return -1;
	}

	xaudio2->StartEngine();

	if (FAILED(xaudio2->CreateMasteringVoice(&masteringVoice)))
	{
		xaudio2->Release();
		pReader->Release();
		//pReader2->Release();	//Homework
		MFShutdown();
		CoUninitialize();
		return -1;
	}

	IMFMediaType* setMediaType;
	MFCreateMediaType(&setMediaType);
	setMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
	setMediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
	pReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, setMediaType);
	//pReader2->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, setMediaType);	//Homework
	setMediaType->Release();

	WAVEFORMATEX* getSourceFormat, sourceFormat;
	unsigned int size;
	IMFMediaType* mediaType;
	pReader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, &mediaType);
	//pReader2->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, &mediaType);		//Homework
	MFCreateWaveFormatExFromMFMediaType(mediaType, &getSourceFormat, &size);
	memcpy(&sourceFormat, getSourceFormat, sizeof(WAVEFORMATEX));
	CoTaskMemFree(getSourceFormat);
	mediaType->Release();


	MyVoiceCallBack callback;
	if (FAILED(xaudio2->CreateSourceVoice(&sourceVoice, &sourceFormat, 0,
		XAUDIO2_DEFAULT_FREQ_RATIO, &callback)) 
		//|| FAILED(xaudio2->CreateSourceVoice(&sourceVoice2, &sourceFormat, 0,
		//	XAUDIO2_DEFAULT_FREQ_RATIO, &callback))
		)
	{
		masteringVoice->DestroyVoice();
		xaudio2->Release();
		pReader->Release();
		//pReader2->Release();	//Homework
		MFShutdown();
		CoUninitialize();
		return -1;
	}

	SubmitBuffer(&callback);
	sourceVoice->Start();
	//sourceVoice2->Start();
	
	while (!callback.isLast);

	sourceVoice->DestroyVoice();
	//sourceVoice2->DestroyVoice();
	masteringVoice->DestroyVoice();

	xaudio2->StopEngine();
	xaudio2->Release();
	pReader->Release();
	//pReader2->Release();	//Homework

	MFShutdown();
	CoUninitialize();

	return 0;
	
}

void SubmitBuffer(MyVoiceCallBack* callback)
{
	IMFSample* sample;
	DWORD flags;
	if (FAILED(pReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags,
		nullptr, &sample)))
		callback->isLast = true;
	else
	{
		if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
			callback->isLast = true;
		else
		{
			IMFMediaBuffer* buffer;
			if (FAILED(sample->ConvertToContiguousBuffer(&buffer)))
				callback->isLast = true;
			else
			{
				XAUDIO2_BUFFER xaudioBuffer = { 0, };
				DWORD bufferLength, maxLength;
				buffer->Lock((BYTE**)&xaudioBuffer.pAudioData, &maxLength, &bufferLength);
				xaudioBuffer.Flags = 0;
				xaudioBuffer.AudioBytes = bufferLength;
				sourceVoice->SubmitSourceBuffer(&xaudioBuffer);
				buffer->Unlock();
				buffer->Release();
			}
			sample->Release();
		}
	}
}