
#include <linux/btree.h>

///---------------------------------------------------------
uint32_t jenkins_one_at_a_time_hash(char *key, size_t len)
{
    uint32_t hash, i;
    for(hash = i = 0; i < len; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}


///---------------------------------------------------------
int main( int argc, char ** argv ) {

	char * input_file;
	FILE * fp;
	node * root;
	int input, range2;
	char instruction;
	char license_part;

	root = NULL;
	verbose_output = false;

	if (argc > 1) {
		order = atoi(argv[1]);
		if (order < MIN_ORDER || order > MAX_ORDER) {
			fprintf(stderr, "Invalid order: %d .\n\n", order);
			usage_3();
			exit(EXIT_FAILURE);
		}
	}

	license_notice();
	usage_1();  
	usage_2();

	if (argc > 2) {
		input_file = argv[2];
		fp = fopen(input_file, "r");
		if (fp == NULL) {
			perror("Failure to open input file.");
			exit(EXIT_FAILURE);
		}
		while (!feof(fp)) {
			fscanf(fp, "%d\n", &input);
			root = insert(root, input, input);
		}
		fclose(fp);
		print_tree(root);
	}

	printf("> ");
	while (scanf("%c", &instruction) != EOF) {
		switch (instruction) {
		case 'd':
			scanf("%d", &input);
			root = delete(root, input);
			print_tree(root);
			break;
		case 'i':
			scanf("%d", &input);
			root = insert(root, input, input);
			print_tree(root);
			break;
		case 'f':
		case 'p':
			scanf("%d", &input);
			find_and_print(root, input, instruction == 'p');
			break;
		case 'r':
			scanf("%d %d", &input, &range2);
			if (input > range2) {
				int tmp = range2;
				range2 = input;
				input = tmp;
			}
			find_and_print_range(root, input, range2, instruction == 'p');
			break;
		case 'l':
			print_leaves(root);
			break;
		case 'q':
			while (getchar() != (int)'\n');
			return EXIT_SUCCESS;
		case 's':
			if (scanf("how %c", &license_part) == 0) {
				usage_2();
				break;
			}
			switch(license_part) {
			case 'w':
				print_license(LICENSE_WARRANTEE);
				break;
			case 'c':
				print_license(LICENSE_CONDITIONS);
				break;
			default:
				usage_2();
				break;
			}
			break;
		case 't':
			print_tree(root);
			break;
		case 'v':
			verbose_output = !verbose_output;
			break;
		case 'x':
			if (root)
				root = destroy_tree(root);
			print_tree(root);
			break;
		default:
			usage_2();
			break;
		}
		while (getchar() != (int)'\n');
		printf("> ");
	}
	printf("\n");

	return EXIT_SUCCESS;
}
