
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


int cmd_add(int argc, const char **argv)
{
	printf("Command add\n");
	return 0;
}

int cmd_branch(int argc, const char **argv)
{
	printf("Command branch\n");
	return 0;
}



struct ht_cmd {
	const char *name;
	int lev;		/* levenshtein */
	int (*fn)(int, const char **);
} commands[] = {
	{"add", 0, cmd_add},
	{"wash", 0, cmd_branch},
	{"zip", 0, cmd_branch},
	{"dish", 0, cmd_branch},
	{"copy", 0, cmd_branch},
	{"branch", 0, cmd_branch},
};


int name_compare(const void *a, const void *b)
{
	struct ht_cmd *a_ = (struct ht_cmd *)a;
	struct ht_cmd *b_ = (struct ht_cmd *)b;

	return strcmp(a_->name, b_->name);
}

int levenshtein(const char *s, const char *t, int d, int a, int us, int w)
{
	int len_s = strlen(s);
	int len_t = strlen(t);
	int *row0 = (int *)malloc(sizeof(int) * (len_t + 1));
	int *row1 = (int *)malloc(sizeof(int) * (len_t + 1));
	int *row2 = (int *)malloc(sizeof(int) * (len_t + 1));
	int i,j;

	for (j = 0; j <= len_t; j++)
		row1[j] = j * a;

	for (i = 0; i < len_s; i++) {
		int *dummy;
		
		row2[0] = (i + 1) * d;
		for (j = 0; j < len_t; j++) {
			/* substitution */
			row2[j + 1] = row1[j] + us * (s[i] != t[j]);
			/* insertion */
			if (row2[j + 1] > row2[j] + a)
				row2[j + 1] = row2[j] + a;
			/* deletion */
			if (row2[j + 1] > row1[j + 1] + d)
				row2[j + 1] = row1[j + 1] + d; 
			/* swap */
			if (i > 0 && j > 0 && s[i - 1] == t[j] && s[i] == t[j - 1] &&
			    row2[j + 1] > row0[j - 1] + w)
				row2[j + 1] = row0[j - 1] + w;
			
		}

		dummy = row0;
		row0 = row1;
		row1 = row2;
		row2 = dummy;		
	}

	i = row1[len_t];
	free(row0);
	free(row1);
	free(row2);

	return i;
}


int main(int argc, char *argv[])
{
	char string_a[2048];
	char string_b[2048];
	
	while (1) {
		printf("String A: ");
		scanf("%s", string_a);
		printf("String B: ");
		scanf("%s", string_b);
		printf("The levenshtein distance is %d\n",
		       levenshtein(string_a, string_b, 1, 1, 1, 1));		
	}
	
	return 0;
}
