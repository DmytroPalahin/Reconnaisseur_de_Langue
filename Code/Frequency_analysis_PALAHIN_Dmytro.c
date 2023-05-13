#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N1 26 
#define N2 676 
#define N3 10000

//	Declaration function:   **********************************************************************

void vis_f(FILE *, FILE *);
void vis(FILE *);
void Mod_text(FILE *, FILE *);
int sum_letters(int *);

//  ***********************************************************************************************

int i;
char data_en[N3];					// input array En text                         
char data_fr[N3];					// input array Fr text
char data_test[N3];					// input array Test text

float prob_letter_en[N1];			// array probability of letter En
float prob_letter_fr[N1];			// array probability of letter Fr
float prob_letter_test[N1];			// array probability of letter Test

float prob_bigramm_en[N2];			// array probability of bigramms En               
float prob_bigramm_fr[N2];			// array probability of bigramms Fr
float prob_bigramm_test[N2];		// array probability of bigramms Test

char array_letter[100];
char array_bigramss_en[N3][2]; 		// array of bigramms En                            
char array_bigramss_fr[N3][2]; 		// array of bigramms Fr
char array_bigramss_test[N3][2]; 	// array of bigramms Test

int index_alph;						// index of all ALPHABET BIGRAMMS 


// char Path_1[100] = "En_text_very_small.txt";
 char Path_1[100] = "En_text.txt";
//char Path_2[100] = "Fr_text_very_small.txt";
 char Path_2[100] = "Fr_text.txt";
// char Path_3[100] = "En_test_very_small.txt";
 char Path_3[100] = "Fr_test.txt";
// char Path_3[100] = "Fr_test_very_small.txt";
// char Path_3[100] = "En_test_one_word.txt";
// char Path_3[100] = "Fr_test_one_word.txt";


int main () { 

// Reading from the file: Different volumes of information
// En_text.txt;            Fr_text.txt;             En_test.txt             Fr_test.txt             ----->  Medium volume
// En_text_small.txt;      Fr_text_small.txt;       En_test_small.txt       Fr_test_small.txt       ----->  Small volume
// En_text_very_small.txt; Fr_text_very_small.txt;  En_test_very_small.txt  Fr_test_very_small.txt  ----->  Very small colume
// En_text_one_word.txt;   Fr_text_one_word.txt;    En_test_one_word.txt    Fr_test_one_word.txt    ----->  Only one word

// Create file for intermediate results
	FILE *results, *results_final;
	results = fopen("RESULTS_INTERMEDIATE_COUNT.txt", "w");
	results_final = fopen("RESULTS_FINAL.txt", "w"); 

//	1) Reading from the file

//  English
    FILE *f1;    
	f1 = fopen(Path_1, "r");
//  f1 = fopen(Path_1, "r");
    
    if (f1 == NULL) {
	 	printf("Error to open file %s", Path_1);
	 	return EXIT_FAILURE;
	}
  
    
//  France
    FILE *f2;
	f2 = fopen(Path_2, "r");
//	f2 = fopen(Path_2, "r");

	if (f2 == NULL) {
	 	printf("Error to open file %s", Path_2);
	 	return EXIT_FAILURE;
 	}
    
//  Test
    FILE *f3;
	f3 = fopen(Path_3, "r");
//	f3 = fopen(Path_3, "r");
    
    if (f3 == NULL) {
	 	printf("Error to open file %s", Path_3);
	 	return EXIT_FAILURE;
	}
    
//	2) Visualization 
unsigned char c; 
	
	fprintf(results, "Text_orig_en : \n");
	vis_f(f1, results);
	fprintf(results, "Text_orig_fr : \n");
	vis_f(f2, results);
	fprintf(results, "Text_orig_test : \n");
	vis_f(f3, results);
	
	fclose(f1);
    fclose(f2);
    fclose(f3);
    
//	3) Removing all characters except ASCII ALPHABET	
//	Create new files with modified texts
	
//	Change to normal symboles

	FILE *f1_m;
	
	f1_m = fopen("MODIFIED_En_text.txt", "w");
	f1 = fopen(Path_1, "r"); 
//  f1 = fopen(Path_1, "r"); 
	Mod_text(f1, f1_m);
	fclose(f1);
    fclose(f1_m);

	FILE *f2_m;

	f2_m = fopen("MODIFIED_Fr_text.txt", "w");
	f2 = fopen(Path_2, "r"); 
//  f2 = fopen(Path_2, "r"); 
	Mod_text(f2, f2_m);
	fclose(f2);
    fclose(f2_m);
	
	FILE *f3_m;

	f3_m = fopen("MODIFIED_TEST.txt", "w");
	f3 = fopen(Path_3, "r"); 
// 	f3 = fopen(Path_3, "r"); 
	Mod_text(f3, f3_m);
	fclose(f3);
    fclose(f3_m);


//	3.1.1) Modified text write to the array for English

	f1_m = fopen("MODIFIED_En_text.txt", "r");
	i = 0;
	fprintf(results, "Modified English text :\n");
	while ( !feof(f1_m) ) {
		fscanf(f1_m, "%c", &c);
		if ( !feof(f1_m) ) {
			data_en[i] = c;
			i++;	
			fprintf(results, "%c", c);
		}
	}
	data_en[i] = '\0';
	fclose(f1_m);
	
	fprintf(results, "\n\n\n");
	fprintf(results, "Frequency analysis of letters in Modified English text");	 
    fprintf(results, "\n");
	
//	3.1.2) Frequency analysis of letters in English text
	int alp_en[N1] = {0};
	i = 0;
    while (data_en[i] != '\0'){                                                      
        if(data_en[i] >= 'a' && data_en[i] <= 'z')
            alp_en[data_en[i] - 'a']++;
        i++;
    }
    
    int sum_of_letters_en = sum_letters(alp_en); // Sum of letters in text
    fprintf(results, "Number of symbols in English : %ld;     Number of letters : %d \n", strlen(data_en), sum_of_letters_en);
		 
    for (i = 0; i < N1; i++){
		prob_letter_en[i] = alp_en[i] / (sum_of_letters_en * 1.0);
		fprintf(results, "letter '%c' - %4d times;              prob: %f\n", i + 'a', alp_en[i], prob_letter_en[i]);
	}

	   	
//	3.2.1) Modified text write to the array for France
	f2_m = fopen("MODIFIED_Fr_text.txt", "r");
	i = 0;
	fprintf(results, "\n\n\n");
	fprintf(results, "Modified France text :\n");
	while ( !feof(f2_m) ) {
		fscanf(f2_m, "%c", &c);
		if ( !feof(f2_m) ) {
			data_fr[i] = c;
			i++;	
			fprintf(results, "%c", c);
		}
	}
	data_fr[i] = '\0';
	fclose(f2_m);
	
	
	fprintf(results, "\n\n\n");	 
 	fprintf(results, "Frequency analysis of letters in Modified France text");	 
    fprintf(results, "\n");
	
//	3.2.2) Frequency analysis of letters in Modified France text
	int alp_fr[N1] = {0};
	i = 0;
    while (data_fr[i] != '\0'){                                                            
        if (data_fr[i] >= 'a' && data_fr[i] <= 'z')
            alp_fr[data_fr[i] - 'a']++;
        i++;
    }
    
    int sum_of_letters_fr = sum_letters(alp_fr); // Sum of letters in text
    fprintf(results, "Number of symbols in France : %ld;     Number of letters : %d \n", strlen(data_fr), sum_of_letters_fr);

    for(i = 0; i < N1; i++){
    	prob_letter_fr[i] = alp_fr[i] / (sum_of_letters_fr * 1.0);
		fprintf(results, "letter '%c' - %4d times;              prob: %f\n", i + 'a', alp_fr[i], prob_letter_fr[i]);
	}


//	3.3.1) Modified text write to the array for TEST
	f3_m = fopen("MODIFIED_TEST.txt", "r");
	i = 0;
	fprintf(results, "\n\n\n");
	fprintf(results, "Modified TEST :\n");
	while ( !feof(f3_m) ) {
		fscanf(f3_m, "%c", &c);
		if ( !feof(f3_m) ) {
			data_test[i] = c;
			i++;	
			fprintf(results, "%c", c);
		}
	}
	data_test[i] = '\0';
	fclose(f3_m);
	
	fprintf(results, "\n\n\n");	 
 	fprintf(results, "Frequency analysis of letters in Modified TEST");	 
    fprintf(results, "\n");
	
//	3.3.2) Frequency analysis of letters in Modified TEST
	int alp_test[N1] = {0};
	i = 0;
    while (data_test[i] != '\0'){                                                            
        if(data_test[i] >= 'a' && data_test[i] <= 'z')
            alp_test[data_test[i] - 'a']++;
        i++;
    }
    
    int sum_of_letters_test = sum_letters(alp_test); // Sum of letters in text
    fprintf(results, "Number of symbols in TEST : %ld;     Number of letters : %d \n", strlen(data_test), sum_of_letters_test);

    for (i = 0; i < N1; i++) {
    	prob_letter_test[i] = alp_test[i] / (sum_of_letters_test * 1.0);
		fprintf(results, "letter '%c' - %4d times;              prob: %f\n", i + 'a', alp_test[i], prob_letter_test[i]);
	}


// 4) Part I **********************************************************************************************************
//    Calculation of the Euclidean measure of the distance between the probability of the appearance of letters in texts
 
// 4.1 Euclidean measure for English and TEST text
	printf("\n\n"); 
	fprintf(results_final, "\n\n");
	printf("Part I *************************************************************************************\n");
	fprintf(results_final, "Part I *************************************************************************************\n");
	printf("Calculation of the Euclidean measure of the distance between the probability of the appearance of letters in texts \n");
	fprintf(results_final, "Calculation of the Euclidean measure of the distance between the probability of the appearance of letters in texts \n");
	printf("\n");
	fprintf(results_final, "\n");
	
	fprintf(results, "\n\n\n");
	fprintf(results, "Part I *************************************************************************************\n");
	fprintf(results, "Calculation of the Euclidean measure of the distance between the probability of the appearance of letters in texts \n");
	fprintf(results, "\n");
	
	float sum_eucliden_en_test = 0;
	for (i = 0; i < N1; i++) {
        float difference_en_test = pow(prob_letter_en[i] - prob_letter_test[i], 2);
		sum_eucliden_en_test = sum_eucliden_en_test + difference_en_test;
  	}
    sum_eucliden_en_test = pow(sum_eucliden_en_test, 0.5);
    printf("Euclidean measure for English and TEST:  %7f\n", sum_eucliden_en_test);
	fprintf(results_final, "Euclidean measure for English and TEST:  %7f\n", sum_eucliden_en_test);
    fprintf(results, "Euclidean measure for English and TEST:  %7f\n", sum_eucliden_en_test);

// 4.2 Euclidean measure for France and TEST text

	float sum_eucliden_fr_test = 0;
	for (i = 0; i < N1; i++) {
        float difference_fr_test = pow(prob_letter_fr[i] - prob_letter_test[i], 2);
		sum_eucliden_fr_test = sum_eucliden_fr_test + difference_fr_test;
	}
    sum_eucliden_fr_test = pow(sum_eucliden_fr_test, 0.5);
    printf("Euclidean measure for France and TEST:  %7f\n", sum_eucliden_fr_test);
	fprintf(results_final, "Euclidean measure for France and TEST:  %7f\n", sum_eucliden_fr_test);
    fprintf(results, "Euclidean measure for France and TEST:  %7f\n", sum_eucliden_fr_test);
 
// 4.3 Comparison of two Euclidean measures of distances  
	printf("\nThe Answer for Part I ----->: "); 
	fprintf(results, "\nThe Answer for Part I ----->: ");
	fprintf(results_final, "\nThe Answer for Part I ----->: ");
	  
	if (sum_eucliden_fr_test <= sum_eucliden_en_test) {
		printf("Input text is France");
		fprintf(results, "Input text is France");
		fprintf(results_final, "Input text is France");
	}
	else {
		printf("Input text is English");
		fprintf(results, "Input text is English");
		fprintf(results_final, "Input text is English");
	}
	printf("\n");
	fprintf(results, "\n");
	fprintf(results_final, "\n");        
	


// 5) Part II ******************************************************************************
//    Calculation of the product of the probabilities of letters in text
	printf("\n\n\n"); 
	fprintf(results_final, "\n\n\n"); 
	printf("Part II ***********************************************************************************\n");
	fprintf(results_final, "Part II ***********************************************************************************\n");
	printf("Calculation of the product of the probabilities of letters in the English text");
	fprintf(results_final, "Calculation of the product of the probabilities of letters in the English text");
	printf("\n");
	fprintf(results_final, "\n");
	
	fprintf(results, "\n\n\n");
	fprintf(results, "Part II ***********************************************************************************\n");
	fprintf(results, "Calculation of the product of the probabilities of letters in the English text");
	fprintf(results, "\n");
	
	int n_letters_test = 3; // The number of letters for product of the probabilities 

// 5.1   Calculation of the product of the probabilities of letters in the TEST as English & France text 
	float product_en_test = 1;
	float product_fr_test = 1;
	for(i = 0; i < n_letters_test; i++) {
		if (data_test[i] != ' '){
			int index = data_test[i] - 'a';
			product_en_test = product_en_test * prob_letter_en[index];
			product_fr_test = product_fr_test * prob_letter_fr[index];
		}
	}
	
    printf("Number of letters in TEST text: %d \n\n", n_letters_test);
 	printf("Product of the probabilities of letters in the TEST text as English: %.20f \n", product_en_test);
 	printf("Product of the probabilities of letters in the TEST text as France : %.20f \n", product_fr_test);
 	
 	fprintf(results, "Number of letters in TEST text: %d \n\n", n_letters_test);
 	fprintf(results, "Product of the probabilities of letters in the TEST text as English: %.20f \n", product_en_test);
 	fprintf(results, "Product of the probabilities of letters in the TEST text as France : %.20f \n", product_fr_test);

	fprintf(results_final, "Number of letters in TEST text: %d \n\n", n_letters_test);
 	fprintf(results_final, "Product of the probabilities of letters in the TEST text as English: %.20f \n", product_en_test);
 	fprintf(results_final, "Product of the probabilities of letters in the TEST text as France : %.20f \n", product_fr_test);
      
	printf("\nThe Answer for Part II -----> : "); 
	fprintf(results, "\nThe Answer for Part II -----> : ");
	fprintf(results_final, "\nThe Answer for Part II -----> : ");
	if (product_fr_test >= product_en_test) {
		printf("Input text is France");
		fprintf(results, "Input text is France");
		fprintf(results_final, "Input text is France");
	}
	else {
		printf("Input text is English");
		fprintf(results, "Input text is English");
		fprintf(results_final, "Input text is English");
	}		
	printf("\n");
	fprintf(results, "\n");
	fprintf(results_final, "\n");



// 6) 	Part III ******************************************************************************
//    	Naive Bayesian Text Classifier (Theorem)   NBT

//		data_en[i]	 		- English text 
//		alp_en[i]		 	- the number of letter [i] (a --> 0, b --> 1, ..., z --> 25) in the English text  
//		sum_of_letters_en	- the sum of ALL letters (a, b, ..., z) in English the text  		
//		prob_letter_en[i]	- the probability of letter [i] (a --> 0, b --> 1, ..., z --> 25) in English the text

//		data_fr[i]	 		- France text 
//		alp_fr[i]		 	- the number of letter [i] (a --> 0, b --> 1, ..., z --> 25) in the France text  
//		sum_of_letters_fr	- the sum of ALL letters (a, b, ..., z) in the France text  		
//		prob_letter_fr[i]	- the probability of letter [i] (a --> 0, b --> 1, ..., z --> 25) in the France text

	printf("\n\n\n");
	printf("Part III ***********************************************************************************\n");
	printf("Naive Bayesian text classifier");
	printf("\n");
	
	fprintf(results, "\n\n\n");
	fprintf(results, "Part III ***********************************************************************************\n");
	fprintf(results, "Naive Bayesian text classifier");
	fprintf(results, "\n");

	fprintf(results_final, "\n\n\n");
	fprintf(results_final, "Part III ***********************************************************************************\n");
	fprintf(results_final, "Naive Bayesian text classifier");
	fprintf(results_final, "\n");
	
//	6.1 The probability of letters in TEST as English text 

	float prob_en = sum_of_letters_en * 1.0 / (sum_of_letters_en + sum_of_letters_fr); // the probability of English text
	float prob_fr = sum_of_letters_fr * 1.0 / (sum_of_letters_en + sum_of_letters_fr); // the probability of France text

	float array_prob_letters_en_fr[N1];                                         
	float array_prob_letters_en[N1];
	float array_prob_letters_fr[N1];
	
	float sum_array_prob_letters_en = 0;
	float sum_array_prob_letters_fr = 0;
	
	i = 0;
	while(data_test[i] != '\0'){
		if (data_test[i] >= 'a' &&  data_test[i] <= 'z') {
			int index = data_test[i] - 'a';
			
        	array_prob_letters_en_fr[index] = 1.0 * (alp_en[index] + alp_fr[index]) / (sum_of_letters_en + sum_of_letters_fr); 
			// the probability of letter [index] for English & France
			
			
			array_prob_letters_en[index] = prob_letter_en[index] * prob_en / array_prob_letters_en_fr[index];	
			// probability letter in TEST as English: in Bayes
			
			
			array_prob_letters_fr[index] = prob_letter_fr[index] * prob_fr / array_prob_letters_en_fr[index];	
			// probability letter in TEST as France: in Bayes
			
																								   
			sum_array_prob_letters_en = sum_array_prob_letters_en + array_prob_letters_en[index]; 
			// sum probability letter in TEST as English: in Bayes
			sum_array_prob_letters_fr = sum_array_prob_letters_fr + array_prob_letters_fr[index]; 
			// sum probability letter in TEST as France: in Bayes
		
		}
		i++;
	}
	
	float sum_prob_letters_en = sum_array_prob_letters_en / sum_of_letters_test;
	float sum_prob_letters_fr = sum_array_prob_letters_fr / sum_of_letters_test;
  		
	printf("\n");
	printf("The probability of letters in TEST as English text  '%f'\n", sum_prob_letters_en);
	printf("The probability of letters in TEST as France text   '%f'\n", sum_prob_letters_fr);
	
	fprintf(results, "\n");
	fprintf(results, "The probability of letters in TEST as English text  '%f'\n", sum_prob_letters_en);
	fprintf(results, "The probability of letters in TEST as France text   '%f'\n", sum_prob_letters_fr);

	fprintf(results_final, "\n");
	fprintf(results_final, "The probability of letters in TEST as English text  '%f'\n", sum_prob_letters_en);
	fprintf(results_final, "The probability of letters in TEST as France text   '%f'\n", sum_prob_letters_fr);
  
    
	printf("\nThe Answer for Part III -----> : ");
	fprintf(results, "\nThe Answer for Part III -----> : ");  
	fprintf(results_final, "\nThe Answer for Part III -----> : ");
	if (sum_prob_letters_en >= sum_prob_letters_fr) {
		printf("Input text is English");
		fprintf(results, "Input text is English");
		fprintf(results_final, "Input text is English");
	}	
	else {
		printf("Input text is France");
		fprintf(results, "Input text is France");
		fprintf(results_final, "Input text is France");
	}		
	printf("\n");
	fprintf(results, "\n");
	fprintf(results_final, "\n");



// 7) Part IV  BIGGRAMS******************************************************************************
//  Calculation of the Euclidean measure of the distance between the probability of the BIGGRAMS in texts 

	fprintf(results, "\n\n\nMethod of TWO BIGGRAMS ********************************************************************* :\n\n");
		
// ***************    TEST text  7.1   ********************************************

// 7.1.1_TEST Creating an array "array_words_test" of words from text	
	fprintf(results, "The array of words from TEST text -------> :\n");
	
	char array_words_test[1000][20];      // the array of words for TEST
	i = 0;
	int k = 0;                            // index of letter in the word
	int row_test = 0;                     // index of word 
	
	while(data_test[i] != '\0'){
		if (data_test[i] != ' '){
			fprintf(results, "%c",  data_test[i]);
			array_words_test[row_test][k] = data_test[i];
			k++; 	
		}
		else {	
			fprintf(results, "\n");
			k = 0;
			row_test++;
		}	
		i++;
	}
	fprintf(results, "\n\n");

	
// 7.1.2_TEST  Creating an array of BIGRAMMS "---array_bigramss_test---" from words in "---array_words_test---"
	int i = 0;
	int j;
	int index_test = 0;

	while (i <= row_test){
		char one_word[100] = {};
		
		if(strlen(array_words_test[i]) > 1) {
			for(j = 0; j < strlen(array_words_test[i]); j++) {
		    	one_word[j] = array_words_test[i][j]; 	// "one_word" ---> array letters for one word "i"
			}
		}

// 7.1.3_TEST  To create BIGRAMMS from all words  "--- array_bigramss_test---"	
	
	   	int word_len = strlen(one_word);
		int ii;	
		for (ii = 0; ii <= word_len - 2; ii++) {
			array_bigramss_test[index_test + ii][0] = one_word[ii];
			array_bigramss_test[index_test + ii][1] = one_word[ii+1];  
		}
		index_test = index_test + ii + 1; // len of bigramm array
		i++;
	}

// 7.1.4_TEST  Print all BIGRAMMS from input text

	fprintf(results, "All BIGRAMMS from TEST text ---------> : \n\n");
	for (i = 0; i < index_test;  i++){
		for (j = 0; j <= 1;  j++)			
			fprintf(results, "%c", array_bigramss_test[i][j]);	
		fprintf(results, " ");
	}
	fprintf(results, "\n\n");


// 7.1.5 BIGRAMMS from ALPHABET -------> N2 = 26 * 26 = 676 
	fprintf(results, "All BIGRAMMS from ALPHABET -------> : \n\n");
	char array_bigramss_alphabet[N2][2];
 // array of bigramms	from ALPHABET
	char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
	index_alph = 0;
	
	for (i = 0; i < 26;  i++){
		for (j = 0; j < 26;  j++){
			array_bigramss_alphabet[index_alph][0] = alphabet[i];
			array_bigramss_alphabet[index_alph][1] = alphabet[j];			
			fprintf(results, " %s", array_bigramss_alphabet[index_alph]);			
			fprintf(results, " ");
			index_alph++;		
		}
	}
	fprintf(results, "\n\n");
	
	
// 7.1.6_TEST BIGRAMMS from ALPHABET: -------> "array_bigramss_alphabet"; BIGRAMMS from input text ---> "array_bigramss_test".

//	"array_equals_test" - the one-dimanssion array as numbers of bigramms from input text
//   and with index in 'array_bigramss_alphabet' [0...676]
	
	int array_equals_test[N2] = {0};
	for (i = 0; i < index_alph;  i++){
		for (j = 0; j < index_test;  j++){
			if (array_bigramss_alphabet[i][0] == array_bigramss_test[j][0]){
				if (array_bigramss_alphabet[i][1] == array_bigramss_test[j][1]){
					array_equals_test[i]++;
				}	
			}		
		}	
	}
	
// Print 1) 'array_equals_test';  2) 'sum of all bigramms';   
// 'prob_bigramm_test' - the array of probability of ALL bigramms in TEST

	int sum_array_equals_test = 0; // The sum of all bigramms from input text
	
	fprintf(results, "Map of bigramms in TEST :\n");
	for (i = 0; i < index_alph;  i++){
		sum_array_equals_test = sum_array_equals_test + array_equals_test[i];
		fprintf(results, " %d", array_equals_test[i]);	
	}
	fprintf(results, "\n\n");
	fprintf(results, "The sum of all bigramms from TEST input text =  %d\n",  sum_array_equals_test);	


// 7.1.7_TEST !!!!!!!!!!   Calculate the probability of ALL bigramms for TEST     !!!!!!!
	for (i = 0; i < index_alph;  i++){
		prob_bigramm_test[i] = array_equals_test[i] / (sum_array_equals_test * 1.0);
//		printf(" %.3f", prob_bigramm_test[i]);	
	}


// ***************    English text  7.2   ********************************************

// 7.2.1_English Creating an array "array_words_en" of words from text	
	fprintf(results, "\n\n");
	fprintf(results, "**************************************************************************************************************\n");
	fprintf(results, "The array of words from English text -------> :\n");
	
	char array_words_en[1000][20];         // the array of words
	i = 0;
	k = 0;                                 // index of letter in the word
	int row_en = 0;                        // index of word
	
	while(data_en[i]){
		if (data_en[i] != ' '){
			fprintf(results, "%c",  data_en[i]);
			array_words_en[row_en][k] = data_en[i];
			k++; 	
		}
		else {
			fprintf(results, "\n");
			k = 0;
			row_en++;
		}	
		i++;
	}
	fprintf(results, "\n\n");
	
// 7.2.2_English Creating an array of BIGRAMMS "---array_bigramss_en---" from words in "---array_words_en---"
	i = 0;
	int index_en = 0;

	while (i <= row_en){
		char one_word[100] = {};
		if(strlen(array_words_en[i]) > 1) {
			for(j = 0; j < strlen(array_words_en[i]); j++) {
		    	one_word[j] = array_words_en[i][j]; 	// "one_word" ---> array letters for one word "i"
			}
		}

// 7.2.3_English  To create BIGRAMMS from all words  "---array_bigramss_en---"	
	
    	int word_len = strlen(one_word);
		int ii;	
		for (ii = 0; ii <= word_len - 2; ii++) {
			array_bigramss_en[index_en + ii][0] = one_word[ii];
			array_bigramss_en[index_en + ii][1] = one_word[ii+1];  
		}
		index_en = index_en + ii + 1; // len of bigramm array
		i++;
	}



// 7.2.4_English  Print all BIGRAMMS from input text

	fprintf(results, "All BIGRAMMS from English text -------> : \n\n");
	for (i = 0; i < index_en;  i++){
		for (j = 0; j <= 1;  j++) 
			fprintf(results, "%c", array_bigramss_en[i][j]);	
		fprintf(results, " ");
	}
	fprintf(results, "\n\n");

// 7.2.5 BIGRAMMS from ALPHABET ---> N2 = 26 * 26 = 676 
	
// 7.2.6_English BIGRAMMS from ALPHABET: ---> "array_bigramss_alphabet" ; BIGRAMMS from input text ---> "array_bigramss_en".

//	"array_equals_test" - the one-dimanssion array as numbers of bigramms from input text and whith index in  'array_bigramss_alphabet' [0...676]
	
	int array_equals_en[N2] = {0};
	for (i = 0; i < index_alph;  i++){
		for (j = 0; j < index_en;  j++){
			if (array_bigramss_alphabet[i][0] == array_bigramss_en[j][0]){
				if (array_bigramss_alphabet[i][1] == array_bigramss_en[j][1]){
					array_equals_en[i]++;
				}	
			}		
		}	
	}
	
// Print 'array_equals_test' and sum of all bigramms
	fprintf(results, "Map of bigramms in English :\n");
	int sum_array_equals_en = 0; // The sum of all bigramms from input text
	for (i = 0; i < index_alph;  i++){
		sum_array_equals_en = sum_array_equals_en + array_equals_en[i];
		fprintf(results, " %d", array_equals_en[i]);	
	}
	fprintf(results, "\n\n");
	fprintf(results, "The sum of all bigramms from English input text =  %d\n",  sum_array_equals_en);	


// 7.2.7._English !!!!!!!!!!   Calculate the probability of ALL bigramms for English     !!!!!!!
	for (i = 0; i < index_alph;  i++){
		prob_bigramm_en[i] = array_equals_en[i] / (sum_array_equals_en * 1.0);
//		printf(" %.3f", prob_bigramm_en[i]);	
	}


// ***************    France text  7.3   ********************************************

// 7.3.1_France Creating an array "array_words_fr" of words from text	
	fprintf(results, "\n\n");
	fprintf(results, "**************************************************************************************************************\n");
	fprintf(results, "The array of words from France text -------> :\n");
	
	char array_words_fr[1000][20];        // the array of words
	i = 0;
	k = 0;                                // index of letter in the word
	int row_fr = 0;                       // index of word
	
	while(data_fr[i]){
		if (data_fr[i] !=' '){
			fprintf(results, "%c",  data_fr[i]);
			array_words_fr[row_fr][k] = data_fr[i];
			k++; 	
		}
		else {
			fprintf(results, "\n");
			k = 0;
			row_fr++;
		}	
		i++;
	}
	fprintf(results, "\n\n");
	
// 7.3.2_France Creating an array of BIGRAMMS "---array_bigramss_fr---" from words in "---array_words_fr---"
	i = 0;
	int index_fr = 0;

	while (i <= row_fr){
		char one_word[100] = {};
		if(strlen(array_words_fr[i]) > 1) {
			for(j = 0; j < strlen(array_words_fr[i]); j++) {
		    	one_word[j] = 	array_words_fr[i][j]; 	// "one_word" ---> array letters for one word "i"
			}
		}

// 7.3.3_France  To create BIGRAMMS from all words  "--- array_bigramss---"	
	
    	int word_len = strlen(one_word);
		int ii;	
		for (ii = 0; ii <= (word_len - 2); ii++) {
			array_bigramss_fr[index_fr + ii][0] = one_word[ii];
			array_bigramss_fr[index_fr + ii][1] = one_word[ii+1];  
		}
		index_fr = index_fr + ii + 1; // len of bigramm array
		i++;
	}



// 7.3.4_France  Print all BIGRAMMS from input text

	fprintf(results, "All BIGRAMMS from France text -------> : \n\n");
	for (i = 0; i < index_fr;  i++){
		for (j = 0; j <= 1;  j++) 
			fprintf(results, "%c", array_bigramss_fr[i][j]);	
		fprintf(results, " ");
	}
	fprintf(results, "\n\n");

// 7.3.5 BIGRAMMS from ALPHABET ---> N2 = 26 * 26 = 676 
	
// 7.3.6_France BIGRAMMS from ALPHABET: --->"array_bigramss_alphabet" ; BIGRAMMS from input text ---> "array_bigramss_fr".

//	"array_equals_fr" - the one-dimanssion array as numbers of bigramms from input text 
//  and whith index in  'array_bigramss_alphabet' [0...676]
	
	int array_equals_fr[N2] = {0};
	for (i = 0; i < index_alph;  i++){
		for (j = 0; j < index_fr;  j++){
			if (array_bigramss_alphabet[i][0] == array_bigramss_fr[j][0]){
				if (array_bigramss_alphabet[i][1] == array_bigramss_fr[j][1]){
					array_equals_fr[i]++;
				}	
			}		
		}	
	}
	
//Print 'array_equals_fr' and sum of all bigramms
	int sum_array_equals_fr = 0; // The sum of all bigramms from input text
	for (i = 0; i < index_alph;  i++){
		sum_array_equals_fr = sum_array_equals_fr + array_equals_fr[i];
		fprintf(results, " %d", array_equals_fr[i]);	
	}
	fprintf(results, "\n\n");
	fprintf(results, "The sum of all bigramms from France input text =  %d\n",  sum_array_equals_fr);	


// 7.3.7_France !!!!!!!!!!   Calculate the probability of ALL bigramms for France     !!!!!!!
	for (i = 0; i < index_alph;  i++){
		prob_bigramm_fr[i] = array_equals_fr[i] / (sum_array_equals_fr * 1.0);
//		printf(" %.3f", prob_bigramm_fr[i]);	
	}


 
// 7.8. Part IV **********************************************************************************************************
//    Calculation of the Euclidean measure of the distance between the probability of the appearance of BIGRAMMS in texts 
//    7.8.1 Euclidean measure for English and TEST BIGRAMMS
	printf("\n\n\n"); 
	printf("Part IV *************************************************************************************\n");
	printf("Calculation of the Euclidean measure of the distance between the probability of the English and TEST BIGRAMMS\n");
	printf("\n");
	
	fprintf(results, "\n\n\n");
	fprintf(results, "Part IV ***********************************************************************************\n");
	fprintf(results, "Calculation of the Euclidean measure of the distance between the probability of the BIGGRAMS in texts \n");
	fprintf(results, "\n");

	fprintf(results_final, "\n\n\n");
	fprintf(results_final, "Part IV ***********************************************************************************\n");
	fprintf(results_final, "Calculation of the Euclidean measure of the distance between the probability of the BIGGRAMS in texts \n");
	fprintf(results_final, "\n");
	
	float sum_eucliden_en_test_bigramms = 0;
	for(i = 0; i < index_alph; i++) {
        float difference_en_test_bigramms = pow(prob_bigramm_en[i] - prob_bigramm_test[i], 2);
		sum_eucliden_en_test_bigramms = sum_eucliden_en_test_bigramms + difference_en_test_bigramms;
 	}
    sum_eucliden_en_test_bigramms = pow(sum_eucliden_en_test_bigramms, 0.5);
    printf("Euclidean measure for English and TEST BIGRAMMS:  %.7f\n", sum_eucliden_en_test_bigramms);
    fprintf(results, "Euclidean measure for English and TEST BIGRAMMS:  %.7f\n", sum_eucliden_en_test_bigramms);
	fprintf(results_final, "Euclidean measure for English and TEST BIGRAMMS:  %.7f\n", sum_eucliden_en_test_bigramms);

//   7.8.2 Euclidean measure for France and TEST BIGRAMMS
	float sum_eucliden_fr_test_bigramms = 0;
	for(i = 0; i < index_alph; i++) {
        float difference_fr_test_bigramms = pow(prob_bigramm_fr[i] - prob_bigramm_test[i], 2);
		sum_eucliden_fr_test_bigramms = sum_eucliden_fr_test_bigramms + difference_fr_test_bigramms;
	}
    sum_eucliden_fr_test_bigramms = pow(sum_eucliden_fr_test_bigramms, 0.5);
    printf("Euclidean measure for France and TEST BIGRAMMS:  %.7f\n", sum_eucliden_fr_test_bigramms);
    fprintf(results, "Euclidean measure for France and TEST BIGRAMMS:  %.7f\n", sum_eucliden_fr_test_bigramms);
	fprintf(results_final, "Euclidean measure for France and TEST BIGRAMMS:  %.7f\n", sum_eucliden_fr_test_bigramms);
 
// 7.8.3 Comparison of two Euclidean measures of distances   
	printf("\nThe Answer for Part IV -----> : "); 
	fprintf(results, "\nThe Answer for Part IV -----> : ");  
	fprintf(results_final, "\nThe Answer for Part IV -----> : "); 
	if (sum_eucliden_en_test_bigramms >= sum_eucliden_fr_test_bigramms) {
		printf("Input text is France");
		fprintf(results, "Input text is France");
		fprintf(results_final, "Input text is France");
	}	
	else {
		printf("Input text is English");
		fprintf(results, "Input text is English");
		fprintf(results_final, "Input text is France");
	}		  
	printf("\n");  
	fprintf(results, "\n");
	fprintf(results_final, "\n");     
	
	
	
// 8. ********************************* Part V Neural Network *********************************
	printf("\n\n\n\n");
	printf("Part V ***********************************************************************************\n");
	printf("Neural Network \n");

	fprintf(results, "\n\n\n\n");
	fprintf(results, "Part V ***********************************************************************************\n");
	fprintf(results, "Neural Network \n");

	fprintf(results_final, "\n\n\n\n");
	fprintf(results_final, "Part V ***********************************************************************************\n");
	fprintf(results_final, "Neural Network \n");


// Feartures : sigmoid activation function, stochastic gradient descent, and mean square error fuction

// Potential improvements :
// Different activation functions
// Different error funnctions
// Arbitrary number of hidden layers
// Read training and test data from a file
// Add visualization of training


#define EPOCH 10000				// number of Epoch  for training
#define numInputs N1 			// 26
#define numHiddenNodes 15		// number of Hidden Nodes
#define numOutputs 1			// number of Ouputs
#define numTrainingSets 2 		// number of training row --> x_len_row_train

const double lr = 1.0;			// learning rate factor

int y_train[numTrainingSets];

double sigmoid(double x) { return 1 / (1 + exp(-x)); }					// activation function - sigmoid
double dSigmoid(double x) { return x * (1 - x); }
double init_weight() { return ((double)rand())/((double)RAND_MAX); } 	// initial setting of coefficients according to a random law


void shuffle(int *array, size_t n){										// row shuffling
    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; i++) {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}


double hiddenLayer[numHiddenNodes];
double outputLayer[numOutputs];
    
double hiddenLayerBias[numHiddenNodes];
double outputLayerBias[numOutputs];

double hiddenWeights[numInputs][numHiddenNodes];
double outputWeights[numHiddenNodes][numOutputs];
    
double training_inputs[numTrainingSets][N1];
			
	for (i = 0; i < numTrainingSets;  i++){
		for (j = 0; j < N1;  j++){
			if (i == 0)
				training_inputs[i][j] = prob_letter_fr[j];
			else 
				training_inputs[i][j] = prob_letter_en[j];
			}
		}
	y_train[0] = 0;
	y_train[1] = 1;

	int n, x;
	for (i = 0; i < numInputs; i++) {
        for (j = 0; j < numHiddenNodes; j++) {
            hiddenWeights[i][j] = init_weight();
        }
    }
    
	for (i = 0; i < numHiddenNodes; i++) {
        hiddenLayerBias[i] = init_weight();
       	for (j = 0; j < numOutputs; j++) {
       		outputWeights[i][j] = init_weight();
       	}
	}
    
	for (i = 0; i < numOutputs; i++) {
		outputLayerBias[i] = init_weight();
 	}

    
   	int trainingSetOrder[numTrainingSets] = {};
	for (i = 0; i < numTrainingSets; i++) {
		trainingSetOrder[i] = i;
 	}

    
    for (n = 0; n < EPOCH; n++) {
        shuffle(trainingSetOrder, numTrainingSets);
        for (x = 0; x < numTrainingSets; x++) {
            
            i = trainingSetOrder[x];
        
// Forward pass           
            for (j = 0; j < numHiddenNodes; j++) {
                double activation = hiddenLayerBias[j];
                for (k = 0; k < numInputs; k++) {
                    activation += training_inputs[i][k] * hiddenWeights[k][j];
                }
                hiddenLayer[j] = sigmoid(activation);
            }
            
            for (j = 0; j < numOutputs; j++) {
                double activation = outputLayerBias[j];
                for (k = 0; k < numHiddenNodes; k++) {
                    activation += hiddenLayer[k] * outputWeights[k][j];
                }
                outputLayer[j] = sigmoid(activation);
            } 
//			printf("Output: %.3f,  Expected Output: %d \n",  outputLayer[0], y_train[i]);  
            
// Backprop
            double deltaOutput[numOutputs];
            double errorOutput;
            for (j = 0; j < numOutputs; j++) {
                errorOutput = y_train[i]-outputLayer[j];
		        deltaOutput[j] = errorOutput * dSigmoid(outputLayer[j]);
			
            }

            
            double deltaHidden[numHiddenNodes];
            for (j = 0; j < numHiddenNodes; j++) {
                double errorHidden = 0.0;
                for(k = 0; k < numOutputs; k++) {
                    errorHidden += deltaOutput[k] * outputWeights[j][k];
                }
                deltaHidden[j] = errorHidden * dSigmoid(hiddenLayer[j]);
            }
            
            for (j = 0; j < numOutputs; j++) {
                outputLayerBias[j] += deltaOutput[j] * lr;
                for (k = 0; k < numHiddenNodes; k++) {
                    outputWeights[k][j] += hiddenLayer[k] * deltaOutput[j] * lr;
                }
            }
            
            for (j = 0; j < numHiddenNodes; j++) {
                hiddenLayerBias[j] += deltaHidden[j] * lr;
                for(k = 0; k < numInputs; k++) {
                    hiddenWeights[k][j] += training_inputs[i][k] * deltaHidden[j] * lr;
                }
            }
        }
    }
    fprintf(results, "\n");
     
     
// Print weights
    fprintf(results, "Final Hidden Weights\n["); 
    for (j = 0; j < numHiddenNodes; j++) {
        fprintf(results, "["); 
        for(k = 0; k < numInputs; k++) {
            fprintf(results, "  %.2f", hiddenWeights[k][j]);
        }
         fprintf(results, "]");
    }
     fprintf(results, "]\n\n");
    
     fprintf(results, "Final Hidden Biases\n[ ");
    for (j = 0; j < numHiddenNodes; j++) {
        fprintf(results, "  %.2f", hiddenLayerBias[j]); 

    }
    fprintf(results, "]\n\n");
    fprintf(results, "Final Output Weights\n"); 
    for (j = 0; j < numOutputs; j++) {
        fprintf(results, "[");
        for (k = 0; k < numHiddenNodes; k++) {
            fprintf(results, " %.2f ", outputWeights[k][j]); 
        }
        fprintf(results, "]\n\n");
    }
    fprintf(results, "Final Output Biases\n[ "); 
    for (j = 0; j < numOutputs; j++) {
        fprintf(results, "  %.2f ", outputLayerBias[j]);
        
    }
     fprintf(results, "]\n\n");
     fprintf(results, "Check model :\n\n");


// Test code for TEST	    
	for (j = 0; j < numHiddenNodes; j++) {
 		double activation = hiddenLayerBias[j];
   		for (k = 0; k < numInputs; k++) {
     		activation += prob_letter_test[k] * hiddenWeights[k][j];
      	}
       	hiddenLayer[j] = sigmoid(activation);
	}
            
 	for (j = 0; j < numOutputs; j++) {
		double activation = outputLayerBias[j];
		for (k = 0; k < numHiddenNodes; k++) {
			activation += hiddenLayer[k] * outputWeights[k][j];
		}
		outputLayer[j] = sigmoid(activation);
	}
            
            
	printf("The Answer for Part V -----> : ");
	fprintf(results, "The Answer for Part V -----> : ");
	fprintf(results_final, "The Answer for Part V -----> : ");
		   
	if (outputLayer[0] >= 0.5) {
		printf("Input text is English, probability of text = %.3f", outputLayer[0]);
		fprintf(results, "Input text is English, probability of text = %.3f", outputLayer[0]);
		fprintf(results_final, "Input text is English, probability of text = %.3f", outputLayer[0]);
	}
	else {
		printf("Input text is France, probability of text = %.3f", 1 - outputLayer[0]);	
		fprintf(results, "Input text is France, probability of text = %.3f", 1 - outputLayer[0]);
		fprintf(results_final, "Input text is France, probability of text = %.3f", 1 - outputLayer[0]);
	}
	printf("\n");
	fprintf(results, "\n");
  
// ****************************************************************************	
	
	
	printf("\n\n\nThe end :-)\n");
	fprintf(results, "\n\n\nThe end :-)\n");
	fprintf(results_final, "\n\n\nThe end :-)\n");
	
	fclose(results);
	fclose(results_final);
	
	return EXIT_SUCCESS;   
}




//	Description of functions:     *************************************************************************


// Function for sum of letters in text
int sum_letters(int *array) {
	int sum_array = 0;
	
	for(i = 0; i < N1; i++)
		sum_array = sum_array + *(array + i);
		
	return sum_array;
}

// Function for visualization of the text in terminal
void vis(FILE *f) {
	unsigned char c;
	
	while ( !feof(f) ) {
		fscanf(f, "%c", &c);
		if ( !feof(f) )             // ---> without double last symbole
			putchar(c); 
	}
	putchar('\n');
	printf("\n\n");	
}

// Function for visualization of the text in file
void vis_f(FILE *f, FILE *f_output) {
	unsigned char c;
	
	while ( !feof(f) ) {
		fscanf(f, "%c", &c);
		if ( !feof(f) )             // ---> without double last symbole
			fprintf(f_output, "%c", c); 
	}
	fprintf(f_output, "\n\n\n");
}

// Function for modifications of the text (stay only Alphabet letters and gap)
void Mod_text(FILE *f, FILE *f_m){
	unsigned char c;
	
	while ( !feof(f) ) {
		fscanf(f, "%c", &c);
		if ( !feof(f) ) {
			if (c == 195)
				c = 42;                                      // ----> *  
			if ((c == 168) || (c == 169) || (c == 170))
		 		c = 101;                                     // ----> e
			if ((c == 160) || (c == 162))
		 		c = 97;                                      // ----> a
			if ((c == 185) || (c == 187))
		 		c = 117;                                     // ----> u
			if (c == 174)
				c = 105;                                     // ----> i
			if (c == 180)
		 		c = 111;                                     // ----> o
			if (c == 167)
		 		c = 99;                                      // ----> c
			if ((c == '\n') || (c == '\t'))
				c = ' ';

			if (c >= 65 && c <= 90)                        // 'A' ... 'Z'
		 		fprintf(f_m, "%c", c + 'a' - 'A');         // 'A' ----> 'a'	 
			if ((c >= 'a' && c <= 'z') || (c == ' '))
				fprintf(f_m, "%c", c);	 
		}
	}
}

//   *************************************************************************************************