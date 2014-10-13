/* Copyright (C) 2003-2013 Runtime Revolution Ltd.
 
 This file is part of LiveCode.
 
 LiveCode is free software; you can redistribute it and/or modify it under
 the terms of the GNU General Public License v3 as published by the Free
 Software Foundation.
 
 LiveCode is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 for more details.
 
 You should have received a copy of the GNU General Public License
 along with LiveCode.  If not see <http://www.gnu.org/licenses/>.  */

#include <foundation.h>
#include <foundation-auto.h>

void MCArithmeticExecAddIntegerToInteger(integer_t p_number, integer_t& x_target)
{
    if (p_number > 0 && INTEGER_MAX - p_number < x_target)
        // overflow
        return;
    else if (p_number < 0 && INTEGER_MIN - p_number > x_target)
        // underflow
        return;
    else
        x_target += p_number;
}

void MCArithmeticExecAddRealToReal(double p_number, double& x_target)
{
    if (p_number > 0 && MAXFLOAT - p_number > x_target)
        // overflow
        return;
    else
        x_target += p_number;
}

void MCArithmeticExecAddNumberToNumber(MCNumberRef p_number, MCNumberRef& x_target)
{
    double t_target, t_number;
    t_target = MCNumberFetchAsReal(x_target);
    t_number = MCNumberFetchAsReal(p_number);
    
    MCArithmeticExecAddRealToReal(t_number, t_target);
    
    //if no error
    MCValueRelease(x_target);
    
    if (t_target <= INTEGER_MAX && t_target >= INTEGER_MIN)
    {
        MCNumberCreateWithInteger(t_target, x_target);
        return;
    }
    
    MCNumberCreateWithReal(t_target, x_target);
}

void MCArithmeticExecSubtractIntegerFromInteger(integer_t p_number, integer_t& x_target)
{
    if (p_number > 0 && INTEGER_MIN + p_number > x_target)
        // overflow
        return;
    else if (p_number < 0 && INTEGER_MAX + p_number < x_target)
        // underflow
        return;
    else
        x_target -= p_number;
}

void MCArithmeticExecSubtractRealFromReal(double p_number, double& x_target)
{
    if (p_number < 0 && MAXFLOAT + p_number < x_target)
        // overflow
        return;
    else
        x_target -= p_number;
}

void MCArithmeticExecSubtractNumberFromNumber(MCNumberRef p_number, MCNumberRef& x_target)
{
    double t_target, t_number;
    t_target = MCNumberFetchAsReal(x_target);
    t_number = MCNumberFetchAsReal(p_number);
    
    MCArithmeticExecSubtractRealFromReal(t_number, t_target);
    
    //if no error
    MCValueRelease(x_target);
    
    if (t_target <= INTEGER_MAX && t_target >= INTEGER_MIN)
    {
        MCNumberCreateWithInteger(t_target, x_target);
        return;
    }
    
    MCNumberCreateWithReal(t_target, x_target);
}

void MCArithmeticExecMultiplyIntegerByInteger(integer_t p_number, integer_t& x_target)
{
    if (p_number > 0 && INTEGER_MAX / p_number < x_target)
        // overflow
        return;
    else if (p_number < 0 && INTEGER_MIN / p_number > x_target)
        // underflow
        return;
    else
        x_target *= p_number;
}

void MCArithmeticExecMultiplyRealByReal(double p_number, double& x_target)
{
    if (p_number < 0 && MAXFLOAT / p_number < x_target)
        // overflow
        return;
    else
        x_target *= p_number;
}

void MCArithmeticExecMultiplyNumberByNumber(MCNumberRef p_number, MCNumberRef& x_target)
{
    double t_target, t_number;
    t_target = MCNumberFetchAsReal(x_target);
    t_number = MCNumberFetchAsReal(p_number);
    
    MCArithmeticExecMultiplyRealByReal(t_number, t_target);
    
    //if no error
    MCValueRelease(x_target);
    
    if (t_target <= INTEGER_MAX && t_target >= INTEGER_MIN)
    {
        MCNumberCreateWithInteger(t_target, x_target);
        return;
    }
    
    MCNumberCreateWithReal(t_target, x_target);
}

void MCArithmeticExecDivideIntegerByInteger(integer_t p_number, integer_t& x_target)
{
    x_target /= p_number;
}

void MCArithmeticExecDivideRealByReal(double p_number, double& x_target)
{
    if (p_number > 0 && p_number < 1 && MAXFLOAT * p_number < x_target)
        // overflow
        return;
    x_target /= p_number;
}

void MCArithmeticExecDivideNumberByNumber(MCNumberRef p_number, MCNumberRef& x_target)
{
    double t_target, t_number;
    t_target = MCNumberFetchAsReal(x_target);
    t_number = MCNumberFetchAsReal(p_number);
    
    MCArithmeticExecDivideRealByReal(t_number, t_target);
    
    //if no error
    MCValueRelease(x_target);
    
    if (t_target <= INTEGER_MAX && t_target >= INTEGER_MIN)
    {
        MCNumberCreateWithInteger(t_target, x_target);
        return;
    }
    
    MCNumberCreateWithReal(t_target, x_target);
}

void MCArithmeticEvalIntegerPlusInteger(integer_t p_left, integer_t p_right, integer_t& r_output)
{
    MCArithmeticExecAddIntegerToInteger(p_left, p_right);
    
    //if no error
    r_output = p_right;
}

void MCArithmeticEvalRealPlusReal(double p_left, double p_right, double& r_output)
{
    MCArithmeticExecAddRealToReal(p_left, p_right);
    
    //if no error
    r_output = p_right;
}

void MCArithmeticEvalNumberPlusNumber(MCNumberRef p_left, MCNumberRef p_right, MCNumberRef& r_output)
{
    MCNumberRef t_number;
    MCNumberCreateWithReal(MCNumberFetchAsReal(p_right), t_number);
    MCArithmeticExecAddNumberToNumber(p_left, t_number);
    
    //if no error
    r_output = t_number;
    return;
    
    //else
    MCValueRelease(t_number);
}

void MCArithmeticEvalIntegerMinusInteger(integer_t p_left, integer_t p_right, integer_t& r_output)
{
    MCArithmeticExecSubtractIntegerFromInteger(p_left, p_right);
    
    //if no error
    r_output = p_right;
}

void MCArithmeticEvalRealMinusReal(double p_left, double p_right, double& r_output)
{
    MCArithmeticExecSubtractRealFromReal(p_left, p_right);
    
    //if no error
    r_output = p_right;
}

void MCArithmeticEvalNumberMinusNumber(MCNumberRef p_left, MCNumberRef p_right, MCNumberRef& r_output)
{
    MCNumberRef t_number;
    MCNumberCreateWithReal(MCNumberFetchAsReal(p_right), t_number);
    MCArithmeticExecSubtractNumberFromNumber(p_left, t_number);
    
    //if no error
    r_output = t_number;
    return;
    
    //else
    MCValueRelease(t_number);
}

void MCArithmeticEvalIntegerTimesInteger(integer_t p_left, integer_t p_right, integer_t& r_output)
{
    MCArithmeticExecMultiplyIntegerByInteger(p_left, p_right);
    
    //if no error
    r_output = p_right;
}

void MCArithmeticEvalRealTimesReal(double p_left, double p_right, double& r_output)
{
    MCArithmeticExecMultiplyRealByReal(p_left, p_right);
    
    //if no error
    r_output = p_right;
}

void MCArithmeticEvalNumberTimesNumber(MCNumberRef p_left, MCNumberRef p_right, MCNumberRef& r_output)
{
    MCNumberRef t_number;
    MCNumberCreateWithReal(MCNumberFetchAsReal(p_right), t_number);
    MCArithmeticExecMultiplyNumberByNumber(p_left, t_number);
    
    //if no error
    r_output = t_number;
    return;
    
    //else
    MCValueRelease(t_number);
}

void MCArithmeticEvalIntegerOverInteger(integer_t p_left, integer_t p_right, integer_t& r_output)
{
    MCArithmeticExecDivideIntegerByInteger(p_left, p_right);
    
    //if no error
    r_output = p_right;
}

void MCArithmeticEvalRealOverReal(double p_left, double p_right, double& r_output)
{
    MCArithmeticExecDivideRealByReal(p_left, p_right);
    
    //if no error
    r_output = p_right;
}

void MCArithmeticEvalNumberOverNumber(MCNumberRef p_left, MCNumberRef p_right, MCNumberRef& r_output)
{
    MCNumberRef t_number;
    MCNumberCreateWithReal(MCNumberFetchAsReal(p_right), t_number);
    MCArithmeticExecDivideNumberByNumber(p_left, t_number);
    
    //if no error
    r_output = t_number;
    return;
    
    //else
    MCValueRelease(t_number);
}

void MCArithmeticEvalIntegerModInteger(integer_t p_left, integer_t p_right, integer_t& r_output)
{
    if (p_right == 0)
        return;
    
    r_output = fmod(p_left, p_right);
}

void MCArithmeticEvalRealModReal(double p_left, double p_right, double& r_output)
{
    double n = 0.0;
    n = p_left / p_right;
    //if (n == MCinfinity)
    
    r_output = fmod(p_left, p_right);
}

void MCArithmeticEvalNumberModNumber(MCNumberRef p_left, MCNumberRef p_right, MCNumberRef& r_output)
{
    double t_left, t_right;
    t_left = MCNumberFetchAsReal(p_left);
    t_right = MCNumberFetchAsReal(p_right);
    
    double t_result;
    MCArithmeticEvalRealModReal(t_left, t_left, t_result);
    
    //if no error
    if (t_result <= INTEGER_MAX && t_result >= INTEGER_MIN)
    {
        MCNumberCreateWithInteger(t_result, r_output);
        return;
    }
    
    MCNumberCreateWithReal(t_result, r_output);
}

void MCArithmeticEvalIntegerWrapInteger(integer_t p_left, integer_t p_right, integer_t& r_output)
{
    if (p_right == 0)
        return;
    
    integer_t t_y;
	t_y = p_left > 0 ? p_right : -p_right;
	if (p_left >= 0)
		r_output = (fmod(p_left - 1, t_y) + 1);
	else
		r_output = -(fmod(-p_left - 1, t_y) + 1);
}

void MCArithmeticEvalRealWrapReal(double p_left, double p_right, double& r_output)
{
    double n = 0.0;
    n = p_left / p_right;
    //if (n == MCinfinity)
    
    double t_y;
	t_y = p_left > 0 ? p_right : -p_right;
	if (p_left >= 0)
		r_output = (fmod(p_left - 1, t_y) + 1);
	else
		r_output = -(fmod(-p_left - 1, t_y) + 1);
}

void MCArithmeticEvalNumberWrapNumber(MCNumberRef p_left, MCNumberRef p_right, MCNumberRef& r_output)
{
    double t_left, t_right;
    t_left = MCNumberFetchAsReal(p_left);
    t_right = MCNumberFetchAsReal(p_right);
    
    double t_result;
    MCArithmeticEvalRealWrapReal(t_left, t_left, t_result);
    
    //if no error
    if (t_result <= INTEGER_MAX && t_result >= INTEGER_MIN)
    {
        MCNumberCreateWithInteger(t_result, r_output);
        return;
    }
    
    MCNumberCreateWithReal(t_result, r_output);
}

void MCArithmeticEvalIntegerIsGreaterThanInteger(integer_t p_left, integer_t p_right, bool& r_output)
{
    r_output = (p_left > p_right);
}

void MCArithmeticEvalRealIsGreaterThanReal(double p_left, double p_right, bool& r_output)
{
    r_output = (p_left > p_right);
}

void MCArithmeticEvalNumberIsGreaterThanNumber(MCNumberRef p_left, MCNumberRef p_right, bool& r_output)
{
    r_output = (MCNumberFetchAsReal(p_left) > MCNumberFetchAsReal(p_right));
}

void MCArithmeticEvalIntegerIsGreaterThanOrEqualToInteger(integer_t p_left, integer_t p_right, bool& r_output)
{
    r_output = (p_left >= p_right);
}

void MCArithmeticEvalRealIsGreaterThanOrEqualToReal(double p_left, double p_right, bool& r_output)
{
    r_output = (p_left >= p_right);
}

void MCArithmeticEvalNumberIsGreaterThanOrEqualToNumber(MCNumberRef p_left, MCNumberRef p_right, bool& r_output)
{
    r_output = (MCNumberFetchAsReal(p_left) >= MCNumberFetchAsReal(p_right));
}

void MCArithmeticEvalIntegerIsLessThanInteger(integer_t p_left, integer_t p_right, bool& r_output)
{
    r_output = (p_left < p_right);
}

void MCArithmeticEvalRealIsLessThanReal(double p_left, double p_right, bool& r_output)
{
    r_output = (p_left < p_right);
}

void MCArithmeticEvalNumberIsLessThanNumber(MCNumberRef p_left, MCNumberRef p_right, bool& r_output)
{
    r_output = (MCNumberFetchAsReal(p_left) < MCNumberFetchAsReal(p_right));
}

void MCArithmeticEvalIntegerIsLessThanOrEqualToInteger(integer_t p_left, integer_t p_right, bool& r_output)
{
    r_output = (p_left <= p_right);
}

void MCArithmeticEvalRealIsLessThanOrEqualToReal(double p_left, double p_right, bool& r_output)
{
    r_output = (p_left <= p_right);
}

void MCArithmeticEvalNumberIsLessThanOrEqualToNumber(MCNumberRef p_left, MCNumberRef p_right, bool& r_output)
{
    r_output = (MCNumberFetchAsReal(p_left) <= MCNumberFetchAsReal(p_right));
}