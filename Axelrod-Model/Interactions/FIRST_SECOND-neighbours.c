
//--FIRST AND SECONDS NEIGHBOURS INTERACTION--
/*I generate a random number from 0 to L*L called "random_active_element" (from a vector).
Then, turn it to matrix notation of the form  n = i*L+j in "i" and "j" through the "/" and "%" division*/
int i=random_active_element/L;
int j=random_active_element%L;
/*Calculate the first neighbours*/
int i_left = i - 1;
int i_right = i + 1;
int j_up = j - 1;
int j_down = j + 1;
/*First neighbours*/
int vecNeigh[] = {i_left,i_right,j_up,j_down};
/*SELECTION PROCESS*/
/*Random selection of the first two vecNeigh elements*/
do
{
	random_fsn1 = rand() % 2;
} while ((vecNeigh[random_fsn1] <0) || (vecNeigh[random_fsn1] >=L));
/*Random selection of the last two vecNeigh elements*/
do
{
	random_fsn2 = 2 + rand() % 2;
} while ((vecNeigh[random_fsn2] <0) || (vecNeigh[random_fsn2] >=L));
random_neigh_1 = vecNeigh[random_fsn1]*L + j;
random_neigh_2 = i*L + vecNeigh[random_fsn2];
/*"random_neigh_1" and "random_neigh_2" are positives or smaller than L, thus "random_second_neigh" is within
the matrix*/
random_second_neigh = vecNeigh[random_fsn2] + vecNeigh[random_fsn1]*L;
/*Vector of the 3 selected elements*/
int selected_elements[3];
/*vector initialization with that elements*/
selected_elements[0] = random_neigh_1;
selected_elements[1] = random_neigh_1;
selected_elements[2] = random_second_neigh;
/*I generate a random number from 0 to 3*/
random_selection = rand() % 3;
/*random selection of that elements*/
if (random_selection == 0)
{
	first_second_neighbour = random_neigh_1;
}
else if (random_selection == 1)
{
	first_second_neighbour = random_neigh_2;
}
else if (random_selection == 2)
{
	first_second_neighbour = random_second_neigh;
}
return first_second_neighbour;
