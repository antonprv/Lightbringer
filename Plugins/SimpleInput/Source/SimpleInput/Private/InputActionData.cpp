// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "InputActionData.h"

bool UInputActionData::GetKeyBindings(
    const FName& ActionName, TArray<FSimpleInputBinding>& OutBindings)
{
    if (Bindings.Find(ActionName))
    {
        OutBindings = Bindings[ActionName].Bindings;
        return true;
    }
    return false;
}

bool UInputActionData::GetAxisBinding(
    const FName& ActionName, TArray<FSimpleInputBindingAxis>& OutAxisBindings)
{
    if (Bindings.Find(ActionName))
    {
        OutAxisBindings = AxisBindings[ActionName].Bindings;
        return true;
    }

    return false;
}