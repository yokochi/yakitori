#include <wrl/client.h>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <memory>
#include <agile.h>
#include <ppltasks.h>
#include "Yakitori.h"
#include "CCApplication.h"

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace Windows::Phone::UI::Input;
using namespace Windows::Graphics::Display;
using namespace concurrency;
USING_NS_CC;

Yakitori::Yakitori()
{
}

void Yakitori::Initialize(CoreApplicationView^ applicationView)
{
	applicationView->Activated +=
		ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &Yakitori::OnActivated);

	CoreApplication::Suspending +=
		ref new EventHandler<SuspendingEventArgs^>(this, &Yakitori::OnSuspending);

	CoreApplication::Resuming +=
		ref new EventHandler<Platform::Object^>(this, &Yakitori::OnResuming);
}

void Yakitori::SetWindow(CoreWindow^ window)
{
    // Specify the orientation of your application here
    // The choices are DisplayOrientations::Portrait or DisplayOrientations::Landscape or DisplayOrientations::LandscapeFlipped
	DisplayProperties::AutoRotationPreferences = DisplayOrientations::Landscape;

	window->VisibilityChanged +=
		ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &Yakitori::OnVisibilityChanged);

	window->Closed += 
		ref new TypedEventHandler<CoreWindow^, CoreWindowEventArgs^>(this, &Yakitori::OnWindowClosed);

	window->PointerPressed +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &Yakitori::OnPointerPressed);

	window->PointerMoved +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &Yakitori::OnPointerMoved);

	window->PointerReleased +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &Yakitori::OnPointerReleased);

    CCEGLView* eglView = new CCEGLView();
	eglView->Create(window);
    eglView->setViewName("Yakitori");
}

void Yakitori::Load(Platform::String^ entryPoint)
{
}

void Yakitori::Run()
{
    CCApplication::sharedApplication()->run();
}

void Yakitori::Uninitialize()
{
}

void Yakitori::OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args)
{
	CCEGLView::sharedOpenGLView()->OnVisibilityChanged(sender, args);
}

void Yakitori::OnWindowClosed(CoreWindow^ sender, CoreWindowEventArgs^ args)
{
	CCEGLView::sharedOpenGLView()->OnWindowClosed(sender, args);
}

void Yakitori::OnPointerPressed(CoreWindow^ sender, PointerEventArgs^ args)
{
	CCEGLView::sharedOpenGLView()->OnPointerPressed(sender, args);
}

void Yakitori::OnPointerMoved(CoreWindow^ sender, PointerEventArgs^ args)
{
	CCEGLView::sharedOpenGLView()->OnPointerMoved(sender, args);
}

void Yakitori::OnPointerReleased(CoreWindow^ sender, PointerEventArgs^ args)
{
	CCEGLView::sharedOpenGLView()->OnPointerReleased(sender, args);
}

void Yakitori::OnActivated(CoreApplicationView^ applicationView, IActivatedEventArgs^ args)
{
	HardwareButtons::BackPressed += ref new EventHandler<BackPressedEventArgs^>(this, &Yakitori::OnBackButtonPressed);   
	CoreWindow::GetForCurrentThread()->Activate();
}

void Yakitori::OnBackButtonPressed(Object^ sender, BackPressedEventArgs^ args)
{
    // Leave args->Handled set to false and the app will quit when user presses the back button on the phone
}

void Yakitori::OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args)
{
	// Save app state asynchronously after requesting a deferral. Holding a deferral
	// indicates that the application is busy performing suspending operations. Be
	// aware that a deferral may not be held indefinitely. After about five seconds,
	// the app will be forced to exit.
	SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();
	//m_renderer->ReleaseResourcesForSuspending();

	create_task([this, deferral]()
	{
		// Insert your code here.

		deferral->Complete();
	});
}
 
void Yakitori::OnResuming(Platform::Object^ sender, Platform::Object^ args)
{
	// Restore any data or state that was unloaded on suspend. By default, data
	// and state are persisted when resuming from suspend. Note that this event
	// does not occur if the app was previously terminated.
	// m_renderer->CreateWindowSizeDependentResources();
}

IFrameworkView^ Direct3DApplicationSource::CreateView()
{
	return ref new Yakitori();
}

[Platform::MTAThread]
int main(Platform::Array<Platform::String^>^)
{
	auto direct3DApplicationSource = ref new Direct3DApplicationSource();
	CoreApplication::Run(direct3DApplicationSource);
	return 0;
}