int binary_search (int n, double x[], double y[], double z)
{
	int i = 0; 
	int j = n - 1; 

	while (j - i > 1)
	{
		int k = (i + j)/2; 

		if (z > x[k])
		{
			i = k; 
		}
		else 
		{
			j = k; 
		}
	}

	return i; 	
}
