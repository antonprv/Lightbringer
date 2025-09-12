// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "InputActionData.h"

bool UInputActionData::GetBinding(
    const FName& ActionName, FSimpleInputBinding& OutBinding)
{
    if (Bindings.Find(ActionName))
    {
        OutBinding = Bindings[ActionName];
        return true;
    }
    return false;
}

bool UInputActionData::GetAxisBinding(
    const FName& ActionName, FSimpleInputBindingAxis& OutAxisBinding)
{
    if (Bindings.Find(ActionName))
    {
        OutAxisBinding = AxisBindings[ActionName];
        return true;
    }
    return false;
}

/*
 * Sets new value to existing binding. Function checks if said ActionName
 * exists and then fails silently if it doesn't.
 *
 * @param ActionName ActionName to search for.
 * @param KeyToPress New key value to set to the Action.
 */
void UInputActionData::SetBinding(const FName& ActionName, FKey& KeyToPress)
{
    if (Bindings.Find(ActionName))
    {
        Bindings[ActionName].KeyToPress = KeyToPress;
    };
};

void UInputActionData::SetAxisBinding(
    const FName& ActionName, FKey& KeyToPress)
{
    if (AxisBindings.Find(ActionName))
    {
        AxisBindings[ActionName].KeyToPress = KeyToPress;
    };
};