//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

using namespace Windows::UI::Xaml::Media::Imaging;

#pragma once

#include "MainPage.g.h"

namespace CRandomDice
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		// This app only allows at most 4 dices thrown at the same time.
		const unsigned int	uMaxNumDices = 4;
		// A dice throwing will read 1, 2, ......, and 6.
		const unsigned int	MAX_DICE_READING = 6;
		unsigned int	uNumDices = 1;
		// Can we use RDRAND from Intel architecture to generate random variables?
		int				bUsingIARDRAND = 0;
		// URL pointing to the dice image locations.
		BitmapImage^		iDice[6];

	private:
		unsigned int	uNextDiceThrown();

	// User interface
	private:
		void ThrowButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void NewDiceNumberButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
