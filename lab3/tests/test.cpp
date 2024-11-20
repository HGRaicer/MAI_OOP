#include <Shapes.h>
#include <gtest\gtest.h>
#include <memory>


TEST(BaseCompare, baseTri) {
    Triangle const tri1{{{0.0f, 0.0f}, {1.0f, 1.0f}, {2.0f, 0.0f}}};
    Triangle const tri2{{{0.0f, 0.0f}, {1.0f, 1.0f}, {2.0f, 0.0f}}};
    ASSERT_TRUE(tri1 == tri2);
}

TEST(BaseCompare, baseSqu) {
    Square const Squ1{{{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}}};
    Square const Squ2{{{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}}};
    ASSERT_TRUE(Squ1 == Squ2);
}

TEST(BaseCompare, baseRec) {
    Rectangle const Rec1{{{0.0f, 0.0f}, {0.0f, 1.0f}, {2.0f, 0.0f}, {2.0f, 1.0f}}};
    Rectangle const Rec2{{{0.0f, 0.0f}, {0.0f, 1.0f}, {2.0f, 0.0f}, {2.0f, 1.0f}}};
    ASSERT_TRUE(Rec1 == Rec2);
}

TEST(RemixCompare, RemTri) {
    Triangle const tri1{{{1.0f, 1.0f}, {0.0f, 0.0f}, {2.0f, 0.0f}}};
    Triangle const tri2{{{0.0f, 0.0f}, {1.0f, 1.0f}, {2.0f, 0.0f}}};
    ASSERT_TRUE(tri1 == tri2);
}

TEST(RemixCompare, RemSqu) {
    Square const Squ1{{{1.0f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f}}};
    Square const Squ2{{{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}}};
    ASSERT_TRUE(Squ1 == Squ2);
}

TEST(RemixCompare, RemRec) {
    Rectangle const Rec1{{{2.0f, 1.0f}, {0.0f, 1.0f}, {2.0f, 0.0f}, {0.0f, 0.0f}}};
    Rectangle const Rec2{{{0.0f, 0.0f}, {0.0f, 1.0f}, {2.0f, 0.0f}, {2.0f, 1.0f}}};
    ASSERT_TRUE(Rec1 == Rec2);
}

TEST(AreaCalc, AreaTri) {
    float constexpr ans = 1.0f;
    Triangle const tri1{{{1.0f, 1.0f}, {0.0f, 0.0f}, {2.0f, 0.0f}}};
    ASSERT_TRUE(tri1.GetArea() == ans);
}

TEST(AreaCalc, AreaSqu) {
    float constexpr ans = 1.0f;
    Square const Squ1{{{1.0f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f}}};
    ASSERT_TRUE(Squ1.GetArea() == ans);
}

TEST(AreaCalc, AreaRec) {
    float constexpr ans = 2.0f;
    Rectangle const Rec1{{{2.0f, 1.0f}, {0.0f, 1.0f}, {2.0f, 0.0f}, {0.0f, 0.0f}}};
    ASSERT_TRUE(Rec1.GetArea() == ans);
}

TEST(polymorphicTest, baseCase) {
    double const answer = 4;

    Triangle s1 {{{1.0f, 1.0f}, {0.0f, 0.0f}, {2.0f, 0.0f}}};
    Square s2 {{{1.0f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f}}};
    Rectangle s3 {{{2.0f, 1.0f}, {0.0f, 1.0f}, {2.0f, 0.0f}, {0.0f, 0.0f}}};

    ShapeArray const container = {
        &s1, &s2, &s3
    };

    double result = 0.0f;
    for (auto& p : container) {
        result += p->GetArea();
    }

    ASSERT_EQ(result, answer);
}






int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

