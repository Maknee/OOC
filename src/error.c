#include "error.h"

static int errorno;

void ClearError()
{
	errorno = NO_ERROR;
}

void SetError(int error)
{
	errorno = error;
}

int CheckError()
{
	return errorno;
}