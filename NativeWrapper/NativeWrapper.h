#pragma once
#include <NativeCalculator.h>
using namespace System;
using namespace System::Runtime::InteropServices;

namespace NativeWrapper {

	public ref class CalculatorWrapper : public System::IDisposable
	{
		NativeCalculator *nativeCalculator;
	public:
		CalculatorWrapper()
		{
			nativeCalculator = new NativeCalculator();
		}
		void Add(cli::array<unsigned char>^ arg1, cli::array<unsigned char>^ arg2, cli::array<unsigned char>^ dst)
		{
			pin_ptr<unsigned char> arg1Pin = &arg1[0];
			pin_ptr<unsigned char> arg2Pin = &arg2[0];
			pin_ptr<unsigned char> dstPin  = &dst[0];

			try
			{
				nativeCalculator->Add(arg1Pin, arg2Pin, dstPin, arg1->Length);
			}
			catch (const std::exception& ex)
			{
				throw gcnew System::Exception(gcnew String(ex.what()));
			}
		}

		void Sum(cli::array<cli::array<unsigned char>^>^ arguments, cli::array<unsigned char>^ output)
		{
			cli::array<GCHandle>^ memoryHandles = gcnew cli::array<GCHandle>(arguments->Length);
			
			try
			{
				std::vector<unsigned char*> nativePtrs(arguments->Length);
				for (int i = 0; i < arguments->Length; i++)
				{
					memoryHandles[i] = GCHandle::Alloc(arguments[0], GCHandleType::Pinned);
					nativePtrs[i] =  (unsigned char*) memoryHandles[i].AddrOfPinnedObject().ToPointer();
				}

				pin_ptr<unsigned char> outputPin = &output[0];

				nativeCalculator->Sum(nativePtrs, outputPin, arguments[0]->Length);

			} catch (const std::exception& ex)
			{
				throw gcnew System::Exception(gcnew String(ex.what()));
			} finally
			{
				for (int i = 0; i < arguments->Length; i++)
				{
					memoryHandles[i].Free();
				}
			}
		}

		~CalculatorWrapper()
		{
			this->!CalculatorWrapper();
		}

		!CalculatorWrapper(){
			delete nativeCalculator;
		}
	};
}
