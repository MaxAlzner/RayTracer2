
#include "..\include\MediaLoader.h"

namespace medialoader
{
	namespace Mesh
	{

		class ObjFileStream
		{
		public:

			static void read(Shape* shape, String filepath);
			static void write(Shape* shape, String filepath);

		};

		MEDIALOADERAPI void Shape::release()
		{
			this->clear();
		}

		MEDIALOADERAPI void Shape::read(String filepath)
		{
			if (filepath.endsWith(".obj"))
			{
				ObjFileStream::read(this, filepath);
			}
		}

		MEDIALOADERAPI void Shape::write(String filepath)
		{
			if (filepath.endsWith(".obj"))
			{
				ObjFileStream::write(this, filepath);
			}
		}

		MEDIALOADERAPI void Shape::clear()
		{
			this->_size = 0;
			if (this->_buffer != 0)
			{
				delete[] this->_buffer;
			}

			this->indices = component<int>();
			this->faceIndices = component<ivec3>();
			this->vertices = component<vec4>();
			this->texcoords = component<vec2>();
			this->normals = component<vec3>();
			this->tangents = component<vec3>();
			this->binormals = component<vec3>();
			this->weights = component<ivec4>();
			this->boneIndices = component<ivec4>();
			this->bones = component<mat4>();
		}

		MEDIALOADERAPI void Shape::normalize()
		{
			float unitSize = 0.0f;
			for (int i = 0; i < this->vertices.elements; i++)
			{
				vec4 v = this->vertices[i];
				if (v.x > unitSize)
				{
					unitSize = v.x;
				}

				if (v.y > unitSize)
				{
					unitSize = v.y;
				}

				if (v.z > unitSize)
				{
					unitSize = v.z;
				}
			}

			for (int i = 0; i < this->vertices.elements; i++)
			{
				this->vertices[i] /= unitSize;
				this->normals[i] = glm::normalize(this->normals[i]);
				this->tangents[i] = glm::normalize(this->tangents[i]);
				this->binormals[i] = glm::normalize(this->binormals[i]);
			}
		}

		MEDIALOADERAPI void Shape::putFace(const int index, const ivec3& face)
		{
			this->faceIndices[index] = face;
		}
		MEDIALOADERAPI void Shape::putVertex(const int index, const vec4& v)
		{
			this->vertices[index] = v;
		}
		MEDIALOADERAPI void Shape::putTexcoord(const int index, const vec2& uv)
		{
			this->texcoords[index] = uv;
		}
		MEDIALOADERAPI void Shape::putNormal(const int index, const vec3& n)
		{
			this->normals[index] = n;
		}
		MEDIALOADERAPI void Shape::putTangent(const int index, const vec3& t)
		{
			this->tangents[index] = t;
		}
		MEDIALOADERAPI void Shape::putBinormal(const int index, const vec3& b)
		{
			this->binormals[index] = b;
		}
		MEDIALOADERAPI void Shape::putWeights(const int index, const ivec4& w)
		{
			this->weights[index] = w;
		}
		MEDIALOADERAPI void Shape::putBoneIndices(const int index, const ivec4& bi)
		{
			this->boneIndices[index] = bi;
		}
		MEDIALOADERAPI ivec3& Shape::getFace(const int index)
		{
			return this->faceIndices[index];
		}
		MEDIALOADERAPI vec4& Shape::getVertex(const int index)
		{
			return this->vertices[index];
		}
		MEDIALOADERAPI vec2& Shape::getTexcoord(const int index)
		{
			return this->texcoords[index];
		}
		MEDIALOADERAPI vec3& Shape::getNormal(const int index)
		{
			return this->normals[index];
		}
		MEDIALOADERAPI vec3& Shape::getTangent(const int index)
		{
			return this->tangents[index];
		}
		MEDIALOADERAPI vec3& Shape::getBinormal(const int index)
		{
			return this->binormals[index];
		}
		MEDIALOADERAPI ivec4& Shape::getWeights(const int index)
		{
			return this->weights[index];
		}
		MEDIALOADERAPI ivec4& Shape::getBoneIndices(const int index)
		{
			return this->boneIndices[index];
		}

		MEDIALOADERAPI bool Shape::isEmpty() const
		{
			return this->_buffer == 0 && this->_size == 0;
		}

		MEDIALOADERAPI const int Shape::elements() const
		{
			return this->vertices.elements;
		}
		MEDIALOADERAPI const int Shape::components() const
		{
			return 5;
		}
		MEDIALOADERAPI const void* Shape::buffer() const
		{
			return this->_buffer;
		}

		void ObjFileStream::read(Shape* shape, String filepath)
		{
			if (shape == 0 || !filepath.endsWith(".obj"))
			{
				return;
			}

			File* file = new File;
			file->read(filepath);

			int vertices = 0;
			int texcoords = 0;
			int normals = 0;
			int faces = 0;

			for (const char* read = file->raw(); read != '\0'; read = strchr(read, '\n'))
			{
				char first = *read;
				if (first == '\n')
				{
					read++;
					first = *read;
				}
				if (first == 'v')
				{
					read++;
					char second = *read;
					if (second == 'n')
					{
						normals++;
					}
					else if (second == 't')
					{
						texcoords++;
					}
					else
					{
						vertices++;
					}
				}
				else if (first == 'f')
				{
					faces++;
				}
			}

			if (faces < 1 || vertices < 1 || texcoords < 1 || normals < 1)
			{
				return;
			}

			int elements = max(vertices, texcoords);
			Array<vec3> rawVertices(vertices);
			Array<vec2> rawTexcoords(texcoords);
			Array<vec3> rawNormals(normals);

			bool orderByVertices = true;
			if (texcoords > vertices)
			{
				orderByVertices = false;
			}

			shape->clear();
			shape->_size = (elements * 15 * sizeof(float)) + (faces * 3 * sizeof(int));
			shape->_buffer = malloc(shape->_size);
			memset(shape->_buffer, 0, shape->_size);

			shape->vertices = component<vec4>((vec4*)shape->_buffer, elements, 0);
			shape->texcoords = component<vec2>(
				(vec2*)(((float*)shape->_buffer) + (elements * 4)),
				elements,
				elements * 4 * sizeof(float));
			shape->normals = component<vec3>(
				(vec3*)(((float*)shape->_buffer) + (elements * 6)),
				elements,
				elements * 6 * sizeof(float));
			shape->tangents = component<vec3>(
				(vec3*)(((float*)shape->_buffer) + (elements * 9)),
				elements,
				elements * 9 * sizeof(float));
			shape->binormals = component<vec3>(
				(vec3*)(((float*)shape->_buffer) + (elements * 12)),
				elements,
				elements * 12 * sizeof(float));
			shape->faceIndices = component<ivec3>(
				(ivec3*)(((float*)shape->_buffer) + (elements * 15)),
				faces,
				elements * 15 * sizeof(float));
			shape->indices = component<int>((int*)shape->faceIndices.buffer, faces * 3, shape->faceIndices.offset);

			int i = 0;
			for (const char* read = file->raw(); read != '\0'; read = strchr(read, '\n'))
			{
				char first = *read;
				if (first == '\n')
				{
					read++;
					first = *read;
				}
				if (*read == 'v')
				{
					char second = *(read + 1);
					if (second == 'n')
					{
						vec3 normal;
						sscanf_s(read, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
						rawNormals.add(normal);
					}
					else if (second == 't')
					{
						vec2 tex;
						sscanf_s(read, "vt %f %f", &tex.x, &tex.y);
						rawTexcoords.add(tex);
					}
					else
					{
						vec3 vert;
						sscanf_s(read, "v %f %f %f", &vert.x, &vert.y, &vert.z);
						rawVertices.add(vert);
					}
				}
				else if (first == 'f')
				{
					ivec3 a, b, c;
					sscanf_s(read, "f %d/%d/%d %d/%d/%d %d/%d/%d", &a.x, &a.y, &a.z, &b.x, &b.y, &b.z, &c.x, &c.y, &c.z);
					a -= 1;
					b -= 1;
					c -= 1;

					int indexA = orderByVertices ? a.x : a.y;
					int indexB = orderByVertices ? b.x : b.y;
					int indexC = orderByVertices ? c.x : c.y;

					shape->putVertex(indexA, vec4(rawVertices[a.x], 1.0f));
					shape->putVertex(indexB, vec4(rawVertices[b.x], 1.0f));
					shape->putVertex(indexC, vec4(rawVertices[c.x], 1.0f));
					shape->putTexcoord(indexA, rawTexcoords[a.y]);
					shape->putTexcoord(indexB, rawTexcoords[b.y]);
					shape->putTexcoord(indexC, rawTexcoords[c.y]);
					shape->putNormal(indexA, rawNormals[a.z]);
					shape->putNormal(indexB, rawNormals[b.z]);
					shape->putNormal(indexC, rawNormals[c.z]);
					shape->putFace(i, ivec3(indexA, indexB, indexC));
					i++;
				}
			}

			rawNormals.clear();
			rawTexcoords.clear();
			rawVertices.clear();

			vec3* facet = new vec3[elements];
			memset(facet, 0, sizeof(vec3) * elements);
			for (int i = 0; i < faces; i++)
			{
				// http://www.terathon.com/code/tangent.html
				ivec3 face = shape->faceIndices[i];
				vec4 va = shape->vertices[face.x];
				vec4 vb = shape->vertices[face.y];
				vec4 vc = shape->vertices[face.z];
				vec2 ta = shape->texcoords[face.x];
				vec2 tb = shape->texcoords[face.y];
				vec2 tc = shape->texcoords[face.z];

				float x1 = vb.x - va.x;
				float x2 = vc.x - va.x;
				float y1 = vb.y - va.y;
				float y2 = vc.y - va.y;
				float z1 = vb.z - va.z;
				float z2 = vc.z - va.z;
				float s1 = tb.x - ta.x;
				float s2 = tc.x - ta.x;
				float t1 = tb.y - ta.y;
				float t2 = tc.y - ta.y;

				float det = 1.0f / ((s1 * t2) - (s2 * t1));
				if (isinf(det))
				{
					det = 0.0f;
				}

				vec3 tangent(((t2 * x1) - (t1 * x2)) * det, ((t2 * y1) - (t1 * y2)) * det, ((t2 * z1) - (t1 * z2)) * det);

				facet[face.x] += tangent;
				facet[face.y] += tangent;
				facet[face.z] += tangent;
			}

			for (int i = 0; i < vertices; i++)
			{
				vec3 normal = shape->normals[i];
				vec3 tangent = normalize(facet[i]);
				vec3 binormal = cross(normal, tangent);

				shape->putTangent(i, tangent);
				shape->putBinormal(i, binormal);
			}

			delete[] facet;
			file->release();
			delete file;
		}
		void ObjFileStream::write(Shape* shape, String filepath)
		{
			if (shape == 0 || filepath.isWhiteSpaceOrEmpty())
			{
				return;
			}

			FILE* file = fopen(filepath, "w");
			if (file == 0)
			{
				return;
			}

			fprintf(file, "\n");
			for (int i = 0; i < shape->vertices.elements; i++)
			{
				vec4 v = shape->vertices[i];
				fprintf(file, "v %f %f %f\n", v.x, v.y, v.z);
			}

			fprintf(file, "\n");
			for (int i = 0; i < shape->normals.elements; i++)
			{
				vec3 n = shape->normals[i];
				fprintf(file, "vn %f %f %f\n", n.x, n.y, n.z);
			}

			fprintf(file, "\n");
			for (int i = 0; i < shape->texcoords.elements; i++)
			{
				vec2 t = shape->texcoords[i];
				fprintf(file, "vt %f %f\n", t.x, t.y);
			}

#if 1
			fprintf(file, "\n");
			for (int i = 0; i < shape->tangents.elements; i++)
			{
				vec3 t = shape->tangents[i];
				fprintf(file, "tan %f %f %f\n", t.x, t.y, t.z);
			}

			fprintf(file, "\n");
			for (int i = 0; i < shape->binormals.elements; i++)
			{
				vec3 b = shape->binormals[i];
				fprintf(file, "bi %f %f %f\n", b.x, b.y, b.z);
			}
#endif

			fprintf(file, "\n");
			for (int i = 0; i < shape->faceIndices.elements; i++)
			{
				ivec3 a = shape->faceIndices[i];
				fprintf(file, "f %d/%d/%d %d/%d/%d %d/%d/%d\n",
					a.x + 1, a.x + 1, a.x + 1,
					a.y + 1, a.y + 1, a.y + 1,
					a.z + 1, a.z + 1, a.z + 1);
			}
		}

	}
}