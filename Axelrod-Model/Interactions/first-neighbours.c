//--FIRST NEIGHBOURS INTERACTION--
/*I generate a random number from 0 to L*L called "random_active_element" (from a vector).
Then, turn it to matrix notation of the form  n = i*L+j in "i" and "j" through the "/" and "%" division*/
int i=random_active_element/L;
int j=random_active_element%L;
/*Calculate the first neighbours*/
int i_left = i - 1;
int i_right = i + 1;
int j_up = j - 1;
int j_down = j + 1;
/*First neighbours neighbours*/
int vecNeigh[] = {i_left,i_right,j_up,j_down};
/*Selection process*/
do {
		random_fn = rand() % 4; 
	} while ( (vecNeigh[random_fn] <0) || (vecNeigh[random_fn] >=L));
random_neighbour = vecNeigh[random_fn];
if (random_fn == 0)
	{firt_neighbour = random_neighbour*L + j;} 
		else if (random_fn == 1)
			{firt_neighbour = random_neighbour*L + j;}
				else if (random_fn == 2)
					{firt_neighbour = i*L + random_neighbour;}
						else if (random_fn == 3){firt_neighbour = i*L + random_neighbour;}
return first_neighbour;
