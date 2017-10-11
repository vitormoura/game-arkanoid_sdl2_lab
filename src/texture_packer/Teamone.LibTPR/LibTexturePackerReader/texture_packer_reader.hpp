#ifndef __texture_packer_reader__
#define __texture_packer_reader__

#include <memory>
#include <map>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

namespace tpckreader {

	using namespace std;
	using namespace rapidxml;

	class sprite {
	public:
		string n;
		int x;
		int y;
		size_t w;
		size_t h;
		float pX;
		float pY;
	};

	class texture_atlas {
	public:
		string image_path;
		size_t width;
		size_t height;
		size_t scale;
		string format;
		map<string,unique_ptr<sprite>> sprites;
	};

	template<class Ch = char>
	class texture_atlas_reader {

	public:

		unique_ptr<texture_atlas> read_texture_atlas(const char* filepath) {

			unique_ptr<texture_atlas> result = make_unique<texture_atlas>();

			if (filepath == nullptr || strlen(filepath) == 0) {
				return result;
			}

			xml_document<> doc;
			unique_ptr<file<>> tmxFile(nullptr);

			try {

				tmxFile.reset(new file<>(filepath));
				doc.parse<0>(tmxFile->data());
				//doc.parse<parse_declaration_node | parse_no_data_nodes>(tmxFile->data());
			}
			catch (std::exception ex) {
				return result;
			}

			auto rootNode = doc.first_node("TextureAtlas");

			if (rootNode != nullptr) {

				for (auto attr = rootNode->first_attribute(); attr; attr = attr->next_attribute()) {

					if (is_name_equals(attr, "imagePath")) {
						read_to(attr, result->image_path);
					}
					else if (is_name_equals(attr, "width")) {
						read_to(attr, &result->width);
					}
					else if (is_name_equals(attr, "height")) {
						read_to(attr, &result->height);
					}
					else if (is_name_equals(attr, "scale")) {
						read_to(attr, &result->scale);
					}
					else if (is_name_equals(attr, "format")) {
						read_to(attr, result->format);
					}
				}

				auto mapChildNode = rootNode->first_node();

				while (mapChildNode != nullptr)
				{
					//<sprite>
					if (is_name_equals(mapChildNode, "sprite")) {

						auto s = make_unique<sprite>();

						for (auto attr = mapChildNode->first_attribute(); attr; attr = attr->next_attribute()) {

							if (is_name_equals(attr, "n")) {
								read_to(attr, s->n);
							}
							else if (is_name_equals(attr, "x")) {
								read_to(attr, &s->x);
							}
							else if (is_name_equals(attr, "y")) {
								read_to(attr, &s->y);
							}
							else if (is_name_equals(attr, "w")) {
								read_to(attr, &s->w);
							}
							else if (is_name_equals(attr, "h")) {
								read_to(attr, &s->h);
							}
							else if (is_name_equals(attr, "pX")) {
								read_to(attr, &s->pX);
							}
							else if (is_name_equals(attr, "pY")) {
								read_to(attr, &s->pY);
							}
						}

						result->sprites[s->n] = move(s);
					}

					mapChildNode = mapChildNode->next_sibling();
				}
			}

			return result;
		}

	private:

		inline void read_to(xml_attribute<Ch>* attr, string& s, bool toUpper = false)
		{
			s.assign(attr->value(), attr->value_size());

			if (toUpper)
				transform(s.begin(), s.end(), s.begin(), toupper);
		}

		inline void read_to(xml_attribute<Ch>* attr, int* i)
		{
			(*i) = atoi(attr->value());
		}

		inline void read_to(xml_attribute<Ch>* attr, size_t* i)
		{
			(*i) = (size_t)atoi(attr->value());
		}

		inline void read_to(xml_attribute<Ch>* attr, bool* b)
		{
			(*b) = atoi(attr->value()) == 1;
		}

		inline void read_to(xml_attribute<Ch>* attr, float* v)
		{
			(*v) = atof(attr->value());
		}


		inline bool is_name_equals(xml_base<Ch>* attr, const char* name)
		{
			return strcmp(attr->name(), name) == 0;
		}

		inline bool is_value_equals(xml_base<Ch>* attr, const char* name)
		{
			return strcmp(attr->value(), name) == 0;
		}
	};
}


#endif // !__texture_packer_reader__