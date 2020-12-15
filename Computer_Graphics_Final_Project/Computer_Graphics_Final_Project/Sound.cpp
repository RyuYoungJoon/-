#pragma once
#include "Sound.h"


void SOUND::PlayerEffect(void)
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
	hr = pGraph->RenderFile(L"Effect1.mp3", NULL);
	if (SUCCEEDED(hr))
	{
		hr = pControl->Run();
		if (SUCCEEDED(hr))
		{
			long evCode;
				pEvent->WaitForCompletion(INFINITE, &evCode);
			//	家府啊 场抄 第 局聪皋捞记 犁积
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
	hr = pGraph->RenderFile(L"浚爹2.wav", NULL);
	if (SUCCEEDED(hr))
	{
		hr = pControl->Run();
		if (SUCCEEDED(hr))
		{
			long evCode;
			pEvent->WaitForCompletion(INFINITE, &evCode);
			//	家府啊 场抄 第 局聪皋捞记 犁积
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
	hr = pGraph->RenderFile(L"Effect1.mp3", NULL);
	if (SUCCEEDED(hr))
	{
		hr = pControl->Run();
		if (SUCCEEDED(hr))
		{
			long evCode;
			//	pEvent->WaitForCompletion(INFINITE, &evCode);
			//	家府啊 场抄 第 局聪皋捞记 犁积
		}
	}
	pControl->Release();
	//pEvent->Release();
	pGraph->Release();
	CoUninitialize();
}
