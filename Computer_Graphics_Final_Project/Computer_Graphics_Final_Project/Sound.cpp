#pragma once
#include "Sound.h"


void SOUND::PlayerEffect()
{
	IGraphBuilder* pGraph = NULL;
	IMediaControl* pControl = NULL;
	IMediaEvent* pEvent = NULL;

	
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		printf("ERROR - Could not initialize COM library");
		return;
	}

	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (void**)&pGraph);
	if (FAILED(hr))
	{
		printf("ERROR - Could not create the Filter Graph Manager.");
		return;
	}

	hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
	hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);


	//hr = pGraph->RenderFile(L"play_fire.wav", NULL);
		hr = pGraph->RenderFile(L"Machine_sound-Marianne_Gagnon-88253407", NULL);
	if (SUCCEEDED(hr))
	{
		hr = pControl->Run();
		if (SUCCEEDED(hr))
		{
			long evCode;
			//	pEvent->WaitForCompletion(INFINITE, &evCode);
			//	소리가 끝난 뒤 애니메이션 재생
		}
	}
	pControl->Release();
	//pEvent->Release();
	pGraph->Release();
	CoUninitialize();
}

void SOUND::PlayerVictory()
{
	IGraphBuilder* pGraph = NULL;
	IMediaControl* pControl = NULL;
	IMediaEvent* pEvent = NULL;


	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		printf("ERROR - Could not initialize COM library");
		return;
	}

	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (void**)&pGraph);
	if (FAILED(hr))
	{
		printf("ERROR - Could not create the Filter Graph Manager.");
		return;
	}

	hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
	hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);


	//hr = pGraph->RenderFile(L"play_fire.wav", NULL);
	hr = pGraph->RenderFile(L"콜라캔 따고 따르는2 (online-audio-converter.com).wav", NULL);
	if (SUCCEEDED(hr))
	{
		hr = pControl->Run();
		if (SUCCEEDED(hr))
		{
			long evCode;
			/*pEvent->WaitForCompletion(INFINITE, &evCode);
				exit(0);*/
			//	소리가 끝난 뒤 애니메이션 재생
		}
	}
	pControl->Release();
	//pEvent->Release();
	pGraph->Release();
	CoUninitialize();
}

void SOUND::PlayerDeath() 
{
	IGraphBuilder* pGraph = NULL;
	IMediaControl* pControl = NULL;
	IMediaEvent* pEvent = NULL;


	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		printf("ERROR - Could not initialize COM library");
		return;
	}

	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (void**)&pGraph);
	if (FAILED(hr))
	{
		printf("ERROR - Could not create the Filter Graph Manager.");
		return;
	}

	hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
	hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);


	//hr = pGraph->RenderFile(L"play_fire.wav", NULL);
	hr = pGraph->RenderFile(L"엔딩2.wav", NULL);
	if (SUCCEEDED(hr))
	{
		hr = pControl->Run();
		if (SUCCEEDED(hr))
		{
			long evCode;
			//	pEvent->WaitForCompletion(INFINITE, &evCode);
			//	소리가 끝난 뒤 애니메이션 재생
		}
	}
	pControl->Release();
	//pEvent->Release();
	pGraph->Release();
	CoUninitialize();
}