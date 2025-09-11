// You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

#include "InputActionData.h"

bool UInputActionData::GetBinding(const FName& ActionName, FSimpleInputBinding& OutBinding)
{
    if (Bindings.Find(ActionName))
    {
        OutBinding = Bindings[ActionName];
        return true;
    }

    return false;
}
