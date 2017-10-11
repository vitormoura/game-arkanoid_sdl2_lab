#include <gtest\gtest.h>
#include "..\LibTexturePackerReader\texture_packer_reader.hpp"

TEST(TexturePackerReader, ExemploTeste) {
		
	using namespace tpckreader;

	texture_atlas_reader<> reader;
	
	auto txt = reader.read_texture_atlas("./texturemap_sample.xml");
		
	EXPECT_TRUE(txt.get() != nullptr);
	ASSERT_EQ(txt->width, 654);
	ASSERT_EQ(txt->height, 654);
	ASSERT_EQ(txt->scale, 1);
	ASSERT_STRCASEEQ(txt->format.c_str(), "RGBA8888");
	ASSERT_EQ(txt->sprites.size(), 78);

	ASSERT_EQ(txt->sprites["buttonSelected.png"]->w, 190);
	ASSERT_EQ(txt->sprites["buttonSelected.png"]->h, 49);
	ASSERT_EQ(txt->sprites["buttonSelected.png"]->x, 1);
	ASSERT_EQ(txt->sprites["buttonSelected.png"]->y, 1);
	ASSERT_EQ(txt->sprites["buttonSelected.png"]->pX, 0.5);
	ASSERT_EQ(txt->sprites["buttonSelected.png"]->pY, 0.5);
	ASSERT_STRCASEEQ(txt->sprites["buttonSelected.png"]->n.c_str(), "buttonSelected.png");

	ASSERT_EQ(txt->sprites["element_green_diamond.png"]->w, 48);
	ASSERT_EQ(txt->sprites["element_green_diamond.png"]->h, 48);
	ASSERT_EQ(txt->sprites["element_green_diamond.png"]->x, 51);
	ASSERT_EQ(txt->sprites["element_green_diamond.png"]->y, 103);
	ASSERT_EQ(txt->sprites["element_green_diamond.png"]->pX, 0.5);
	ASSERT_EQ(txt->sprites["element_green_diamond.png"]->pY, 0.5);
	ASSERT_STRCASEEQ(txt->sprites["element_green_diamond.png"]->n.c_str(), "element_green_diamond.png");
	
}