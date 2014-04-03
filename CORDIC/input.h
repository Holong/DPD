#define TEST_VECTOR_LENGTH	100

struct rect {
	double x;
	double y;
};

struct rect test_vector_for_sqrt[TEST_VECTOR_LENGTH];
double test_vector_for_tri[TEST_VECTOR_LENGTH];

double answer_vector_for_sqrt[TEST_VECTOR_LENGTH];
double answer_vector_for_atan[TEST_VECTOR_LENGTH];
double answer_vector_for_cos[TEST_VECTOR_LENGTH];
double answer_vector_for_sin[TEST_VECTOR_LENGTH];

double CORDIC_answer_vector_for_sqrt[TEST_VECTOR_LENGTH];
double CORDIC_answer_vector_for_atan[TEST_VECTOR_LENGTH];
double CORDIC_answer_vector_for_cos[TEST_VECTOR_LENGTH];
double CORDIC_answer_vector_for_sin[TEST_VECTOR_LENGTH];
