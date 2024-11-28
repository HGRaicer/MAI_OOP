#include "Shapes.h"
#include <gtest\gtest.h>
#include <memory>
#include "ShapeArray.h"


TEST(BaseCompare, baseTri) {
    Triangle<float> const tri1{{{0.0f, 0.0f}, {1.0f, 1.0f}, {2.0f, 0.0f}}};
    Triangle<float> const tri2{{{0.0f, 0.0f}, {1.0f, 1.0f}, {2.0f, 0.0f}}};
    ASSERT_TRUE(tri1 == tri2);
}

TEST(BaseCompare, baseSqu) {
    Square<float> const Squ1{{{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}}};
    Square<float> const Squ2{{{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}}};
    ASSERT_TRUE(Squ1 == Squ2);
}

TEST(BaseCompare, baseRec) {
    Rectangle<float> const Rec1{{{0.0f, 0.0f}, {0.0f, 1.0f}, {2.0f, 0.0f}, {2.0f, 1.0f}}};
    Rectangle<float> const Rec2{{{0.0f, 0.0f}, {0.0f, 1.0f}, {2.0f, 0.0f}, {2.0f, 1.0f}}};
    ASSERT_TRUE(Rec1 == Rec2);
}

TEST(RemixCompare, RemTri) {
    Triangle<float> const tri1{{{1.0f, 1.0f}, {0.0f, 0.0f}, {2.0f, 0.0f}}};
    Triangle<float> const tri2{{{0.0f, 0.0f}, {1.0f, 1.0f}, {2.0f, 0.0f}}};
    ASSERT_TRUE(tri1 == tri2);
}

TEST(RemixCompare, RemSqu) {
    Square<float> const Squ1{{{1.0f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f}}};
    Square<float> const Squ2{{{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}}};
    ASSERT_TRUE(Squ1 == Squ2);
}

TEST(RemixCompare, RemRec) {
    Rectangle<float> const Rec1{{{2.0f, 1.0f}, {0.0f, 1.0f}, {2.0f, 0.0f}, {0.0f, 0.0f}}};
    Rectangle<float> const Rec2{{{0.0f, 0.0f}, {0.0f, 1.0f}, {2.0f, 0.0f}, {2.0f, 1.0f}}};
    ASSERT_TRUE(Rec1 == Rec2);
}

TEST(AreaCalc, AreaTri) {
    float constexpr ans = 1.0f;
    Triangle<float> const tri1{{{1.0f, 1.0f}, {0.0f, 0.0f}, {2.0f, 0.0f}}};
    ASSERT_TRUE(tri1.GetArea() == ans);
}

TEST(AreaCalc, AreaSqu) {
    float constexpr ans = 1.0f;
    Square<float> const Squ1{{{1.0f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f}}};
    ASSERT_TRUE(Squ1.GetArea() == ans);
}

TEST(AreaCalc, AreaRec) {
    float constexpr ans = 2.0f;
    Rectangle<float> const Rec1{{{2.0f, 1.0f}, {0.0f, 1.0f}, {2.0f, 0.0f}, {0.0f, 0.0f}}};
    ASSERT_TRUE(Rec1.GetArea() == ans);
}

TEST(polymorphicTest, baseCase) {
    double constexpr answer = 4;

    auto s1 = std::make_shared<Triangle<float>>(Triangle<float>{{{1.0f, 1.0f}, {0.0f, 0.0f}, {2.0f, 0.0f}}});
    auto s2 = std::make_shared<Square<float>>(Square<float>{{{1.0f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 1.0f}}});
    auto s3 = std::make_shared<Rectangle<float>>(Rectangle<float>{{{2.0f, 1.0f}, {0.0f, 1.0f}, {2.0f, 0.0f}, {0.0f, 0.0f}}});

    auto const container = std::vector<std::shared_ptr<Shape<float>>>{s1, s2, s3};

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

