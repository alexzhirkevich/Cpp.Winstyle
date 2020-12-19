//
// Progressbar.h
//
//      By Alexandr Zhirkevich.
//		E-mail: mailto:sasha.zhirkevich@yandex.ru;
//		Vk: https://vk.com/id175640630;
//		Telegram: @alexzhirkevich.
//
// The C++ WinApi <winstyle.h> library.
//
// namespace wstyle
//

#ifndef _WINSTYLE_PROGRESSBAR_
#define _WINSTYLE_PROGRESSBA_

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER


#include "Init.h"
#include "Control.h"

namespace wstyle {

	class ProgressBar : public Control
	{
	protected:
		size_t stepsCount;
		int currentStep;
		void Clone(const ProgressBar& pb);
	public:
		ProgressBar(const ProgressBar& pb);
		ProgressBar& operator = (const ProgressBar& pb);
		ProgressBar(Window* form, size_t nSteps);
		bool SetStepsCount(size_t nSteps);
		bool SetStep(UINT step);
		bool AddStep(UINT nSteps = 1);
		size_t GetStepsCount();
		~ProgressBar();
	};

}

#endif // _WINSTYLE_PROGRESSBA_