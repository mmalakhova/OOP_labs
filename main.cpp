#include <string>
#include "RNA.h"
#include <gtest/gtest.h>

RNA creation(const std :: string& str_of_nuc) {
    RNA rna;
    for (char i : str_of_nuc){
        switch (i) {
            case 'A':
                rna.add_nucl(A);
                break;
            case 'G':
                rna.add_nucl(G);
                break;
            case 'C':
                rna.add_nucl(C);
                break;
            case 'T':
                rna.add_nucl(T);
            default:
                break;
        }
    }
    return rna;
}


TEST(test_creation, test_1)/* NOLINT */
{
    RNA r1;
    RNA r2;
    r1 = creation("AGTAAAAAAAAA");
    r2 = creation("AGTAAAAAAAAA");
    EXPECT_EQ(true, r1 == r2);
}

TEST(test_constructor, test_2)/* NOLINT */
{
    RNA r1;
    RNA r2;
    EXPECT_EQ(true , r1 == r2);
}

TEST (test_creation, test_3)/* NOLINT */
{
    RNA r1;
    RNA r2;
    r1 = creation("CTCTCTC");
    r2 = creation("GAGAGAG");
    EXPECT_EQ(false, r1 == r2);
}

TEST (test_creation, test_4)/* NOLINT */
{
    RNA r1;
    RNA r2;
    r1 = creation("CTCTCTC");
    r2 = creation("GAGAGAG");
    EXPECT_EQ(true, r1 != r2);
}

TEST (test_operator_assign, test_5)/* NOLINT */
{
    RNA r1 = creation("AAA");
    RNA r2;
    r2 = r1;
    EXPECT_EQ(true, r2 == r1);
}

TEST (test_operator_assign, test_6)/* NOLINT */
{
    RNA r1;
    RNA r2;
    r2 = r1;
    EXPECT_EQ(true, r2 == r1);
}

TEST (test_copyconstructor, test_7)/* NOLINT */
{
    RNA r1;
    RNA r2(r1);
    EXPECT_EQ(true, r1 == r2);
}

TEST (test_copyconstructor, test_8)/* NOLINT */
{
    RNA r1;
    r1 = creation("AACCTTGG");
    RNA r2(r1);
    EXPECT_EQ(true, r1==r2);
}

TEST ( test_operator_add, test_9)/* NOLINT */
{
    RNA r1;
    RNA r2;
    RNA r3 = r1 + r2;
    EXPECT_EQ(true, r3 == r1);
}

TEST ( test_operator_add, test_10)/* NOLINT */
{
    RNA r1 = creation("AAA");
    RNA r2 = creation("TTT");
    RNA r3 = creation("AAATTT");
    RNA r4 = r1 + r2;
    EXPECT_EQ(true, r3 == r4);
}

TEST (test_operator_add, test_11)/* NOLINT */
{
    RNA r1 ;
    RNA r2 ;
    RNA r3 = r1 + r2;
    RNA r4 = r2 + r1;
    EXPECT_EQ(true, r3 == r4);
}

TEST (test_operator_neg, test_12)/* NOLINT */
{
    RNA r1;
    RNA r2;
    r2 = !r1;
    EXPECT_EQ( true, r1 == r2);
}


TEST ( test_operator_neg, test_13)/* NOLINT */
{
    RNA r1 = creation("CACACACACA");
    RNA r2 = creation("GTGTGTGTGT");
    EXPECT_EQ(true, r1 == !r2);
}

TEST (test_complimentary, test_14)/* NOLINT */
{
    RNA r1;
    RNA r2;
    EXPECT_EQ(true, r1.is_Complementary(r2));
}

TEST( test_complimentary, test_15)/* NOLINT */
{
    RNA r1 = creation("CACACACACA");
    RNA r2 = creation("GTGTGTGTGT");
    EXPECT_EQ(true, r1.is_Complementary(r2));
}

TEST (test_sq_brackets_cast, test_16)/* NOLINT */
{
    std :: string r1 = "ATGCCGTAATGCCGTA";
    RNA r2;
    r2 = creation(r1);
    nucls n;

    for (size_t i = 0; i < r1.length(); i++){
        switch (r1[i]) {
            case 'A':
                n = A;
                break;
            case 'G':
                n = G;
                break;
            case 'C':
                n = C;
                break;
            case 'T':
                n = T;
            default:
                break;
        }
        EXPECT_EQ(n, static_cast<nucls>(r2[i+1]));
    }
}

TEST(test_sq_brackets_cast, test_17)/* NOLINT */
{
    std :: string r1 = "AGGGTCGATAACGTAAGCAGATGACAAGCAGATGAC";
    RNA r2;
    nucls n;
    r2 = creation("AGGGTCGATAACGTAAGCAGATGACAAGCAGATGAC");

    for ( size_t i =0; i < r1.length(); i ++){
        switch (r1[i]) {
            case 'A':
                n = A;
                break;
            case 'G':
                n = G;
                break;
            case 'C':
                n = C;
                break;
            case 'T':
                n = T;
            default:
                break;
        }
        EXPECT_EQ(n, static_cast<nucls>(r2[i+1]));
    }
}

TEST(test_sq_brackets_insert, test_18)/* NOLINT */
{
    RNA r1 = creation("AAAAAAAAAAAAAAAAAAAA");
    std :: string str = "AGTAGCTAGCAATCGTAGCA";
    RNA r2;
    r2 = creation(str);
    nucls n;

    for ( size_t i = 0; i< str.length(); i++){
        switch (str[i]) {
            case 'A':
                n = A;
                break;
            case 'G':
                n = G;
                break;
            case 'C':
                n = C;
                break;
            case 'T':
                n = T;
            default:
                break;
        }
        r1[i+1] = n;
    }
    EXPECT_EQ(true, r1 == r2);
}

TEST (test_sq_brackets_insert, test_19)/* NOLINT */
{
    std :: string s1 = "ACGTTTAAAGCGGCATAGC";
    std :: string s2 = "AACGAGATTTAGCGGCAGG";
    RNA r1, r2;
    r1 = creation(s1);
    r2 = creation(s2);

    for ( size_t i = 1 ; i <= (s1.length()); i++){
        r1[i] = r2[i];
    }
    EXPECT_EQ(true, r1 == r2);
}

TEST(test_million_nucls, test_20)/* NOLINT */
{
    RNA r1;
    RNA r2;
    for ( size_t i = 0 ; i < 1000000; i++){
        r1.add_nucl(C);
    }
    EXPECT_FALSE(r1 == r2);
}


int main(int argc, char* argv[]) {
    testing :: InitGoogleTest(&argc, argv);

    RNA rna_test1, rna_test2, rna_test3;
    rna_test1 = creation("AGTAAAAAAAAA");
    rna_test2 = creation("AAA");
    rna_test3 = creation("AGTAAAAAAAAA");

    RNA rna2(rna_test1);

    RNA r1 = creation("CGACGA");
    RNA r2 = creation("GCTGCT");
    RNA r3 = r1 + r2;

    return RUN_ALL_TESTS();
}
