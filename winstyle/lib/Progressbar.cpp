#include "../include/Progressbar.h"

wstyle::ProgressBar::ProgressBar(Window* form, size_t nSteps): Control(form, ControlType::ProgressBar) {
	stepsCount = nSteps;
	currentStep = 0;
	Create(0, 0, 0, 0, style);
}

bool wstyle::ProgressBar::SetStepsCount(size_t nSteps)
{
	if (!hWnd)
		return false;
	stepsCount = nSteps;
	currentStep = 0;
	SendMessage(hWnd, PBM_SETSTEP, (WPARAM)1, 0);
	SendMessage(hWnd, PBM_SETRANGE, 0, (LPARAM)MAKELONG(0, nSteps));
	return true;
}

inline wstyle::ProgressBar::ProgressBar(const ProgressBar& pb): Control(pb.owner,ControlType::ProgressBar) {
	Clone(pb);
}

inline bool wstyle::ProgressBar::AddStep(UINT nSteps) {
	
	if (!hWnd)
		return false;

	currentStep += nSteps;
	for (UINT i = 0; i < nSteps; i++) {
		SendMessage(hWnd, PBM_STEPIT, 0, 0);
	}
	return true;
}

bool wstyle::ProgressBar::SetStep(UINT step)
{
	if (!hWnd || step > stepsCount)
		return false;

	currentStep = step;
	SendMessage(hWnd, PBM_SETPOS, step, 0);
	return true;
}

inline void wstyle::ProgressBar::Clone(const ProgressBar& pb) {
	__super::Clone(pb);
	RECT r = pb.GetRectangle();
	Create(r.left, r.top, r.right - r.left, r.bottom - r.top, style);
	SetStepsCount(pb.stepsCount);
}

inline wstyle::ProgressBar& wstyle::ProgressBar::operator=(const ProgressBar& pb) {
	if (this == &pb)
		return *this;
	Delete();
	Clone(pb);
	return *this;
}