//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace CRandomDice;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

using namespace Windows::UI::Xaml::Media::Imaging;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

// This project is built from "Create a "hello world" app in C++ (Windows 10)" in
// https://msdn.microsoft.com/en-us/windows/uwp/get-started/create-a-basic-windows-10-app-in-cpp

MainPage::MainPage()
{
	InitializeComponent();

	// Initializing the app.
	// Setting up the dice image URLs.
	iDice[0] = ref new BitmapImage(ref new Uri("ms-appx:///Assets/dice1.png"));
	iDice[1] = ref new BitmapImage(ref new Uri("ms-appx:///Assets/dice2.png"));
	iDice[2] = ref new BitmapImage(ref new Uri("ms-appx:///Assets/dice3.png"));
	iDice[3] = ref new BitmapImage(ref new Uri("ms-appx:///Assets/dice4.png"));
	iDice[4] = ref new BitmapImage(ref new Uri("ms-appx:///Assets/dice5.png"));
	iDice[5] = ref new BitmapImage(ref new Uri("ms-appx:///Assets/dice6.png"));

#if defined (_M_X64) || defined(_M_IX86)
	// We activiate the following block only for Win32 and x64.
	{
		// Initializing bUsingIARDRAND to see if we can use IA RDRAND intrinsic.
		unsigned int	uDummy;
		bUsingIARDRAND = _rdrand32_step(&uDummy);
	}
#endif

	if (!bUsingIARDRAND)
	{
		// Setting random number seed.  This should be really random (unpredictable).
		// Using 0 as the random seed during tests.
		// srand(0);
		// Unlike Win32 applications, in Universal Windows we cannot make use of GetTickCount().
		time_t	currentTime;

		time(&currentTime);
		srand(currentTime & 0x0000ffff);
	}
}

unsigned int	CRandomDice::MainPage::uNextDiceThrown()
{
	unsigned int	uRandNum;

#if defined (_M_X64) || defined(_M_IX86)
	// We activiate the following block only for Win32 and x64.
	if (bUsingIARDRAND)
	{
		// RDRAND can be used on this device.  Using it to generate the next random dice throwing.  Check
		// https://software.intel.com/en-us/node/523864 for more details.
		_rdrand32_step(&uRandNum);
	}
	else
#endif
	{
		// RDRAND cannot be used.  Fall back to rand().
		uRandNum = rand();
	}
	// Generating a random number in the range 1..MAX_DICE_READING.
	return (uRandNum % MAX_DICE_READING) + 1;
}

void CRandomDice::MainPage::NewDiceNumberButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// Incrementing the number of dices.  If it exceeds uMaxNumDices, reset it back to 1.
	uNumDices++;
	if (uNumDices > uMaxNumDices)
		uNumDices = 1;

	// When changing the number of dices, we temporarily make all dices invisible.
	dice0->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	dice1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	dice2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	dice3->Visibility = Windows::UI::Xaml::Visibility::Collapsed;

	greetingOutput->Text = "Current Number of Dices: " + uNumDices;
}


void CRandomDice::MainPage::ThrowButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	unsigned int	uDiceTotal = 0;
	unsigned int	uDiceResults[4];

	for (unsigned int i = 0; i < uNumDices; i++)
	{
		uDiceResults[i] = uNextDiceThrown();
		uDiceTotal += uDiceResults[i];
	}

	// Update the total of the dices.
	greetingOutput->Text = "  Total: " + uDiceTotal + ".";

	// Displaying the dices.  How many do we display?
	dice0->Visibility = Windows::UI::Xaml::Visibility::Visible;
	dice0->Source = iDice[uDiceResults[0] - 1];

	// Deciding whether we want to show the nth dice and its reading.
	if (uNumDices > 1)
	{
		dice1->Visibility = Windows::UI::Xaml::Visibility::Visible;
		dice1->Source = iDice[uDiceResults[1] - 1];
	}
	else
		dice1->Visibility = Windows::UI::Xaml::Visibility::Collapsed;

	if (uNumDices > 2)
	{
		dice2->Visibility = Windows::UI::Xaml::Visibility::Visible;
		dice2->Source = iDice[uDiceResults[2] - 1];
	}
	else
		dice2->Visibility = Windows::UI::Xaml::Visibility::Collapsed;

	if (uNumDices > 3)
	{
		dice3->Visibility = Windows::UI::Xaml::Visibility::Visible;
		dice3->Source = iDice[uDiceResults[3] - 1];
	}
	else
		dice3->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
}
