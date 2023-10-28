char CHAR = Input();
if(CHAR == a)
{
	Accept();
	char CHAR = Input();
}
else
if(CHAR == b)
{
	Accept();
	char CHAR = Input();
}
else
	Error(0);
char CHAR = Input();
if(CHAR == b)
{
	Accept();
	char CHAR = Input();
	while(CHAR == c||CHAR == d)
	{
		Accept();
		CHAR = Input();
	}
	if(CHAR == a)
	{
		char CHAR = Input();
		if(CHAR == b)
		{
			Accept();
			char CHAR = Input();
			while(CHAR == c||CHAR == d)
			{
				Accept();
				CHAR = Input();
			}
			if(CHAR == a)
			{
				char CHAR = Input();
				if(CHAR == b)
				{
				}
				else
					Error(0);
			}
			else
				Error(1);
		}
		else
			Error(0);
	}
	else
		Error(1);
}
else
	Error(0);

