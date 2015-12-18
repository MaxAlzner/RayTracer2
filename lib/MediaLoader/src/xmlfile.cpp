
#include "..\include\MediaLoader.h"

namespace medialoader
{

	MEDIALOADERAPI void XmlFile::release()
	{
		this->root = 0;
		if (this->document != 0)
		{
			this->document->clear();
			delete this->document;
		}

		this->document = 0;
		File::release();
	}

	MEDIALOADERAPI void XmlFile::read(String filepath)
	{
		File::read(filepath);
		if (!File::isEmpty())
		{
			this->document = new XmlDocument();
			this->document->parse<0>(this->_raw);
			this->root = this->document->first_node();
			this->_parse();
		}
	}

	MEDIALOADERAPI void XmlFile::_parse()
	{
	}

	MEDIALOADERAPI int XmlFile::ParseInt(XmlNode* node, int defaultValue)
	{
		if (node == 0) return defaultValue;
		char* value = node->value();
		if (value == 0) return defaultValue;

		return atoi(value);
	}
	MEDIALOADERAPI int XmlFile::ParseInt(XmlAttribute* attr, int defaultValue)
	{
		if (attr == 0) return defaultValue;
		char* value = attr->value();
		if (value == 0) return defaultValue;

		return atoi(value);
	}
	MEDIALOADERAPI float XmlFile::ParseFloat(XmlNode* node, float defaultValue)
	{
		if (node == 0) return defaultValue;
		char* value = node->value();
		if (value == 0) return defaultValue;

		return (float)atof(value);
	}
	MEDIALOADERAPI float XmlFile::ParseFloat(XmlAttribute* attr, float defaultValue)
	{
		if (attr == 0) return defaultValue;
		char* value = attr->value();
		if (value == 0) return defaultValue;

		return (float)atof(value);
	}
	MEDIALOADERAPI bool XmlFile::ParseBool(XmlNode* node, bool defaultValue)
	{
		if (node == 0) return defaultValue;
		char* value = node->value();
		if (value == 0) return defaultValue;

		if (strstr(value, "true") != 0) return true;
		return false;
	}
	MEDIALOADERAPI bool XmlFile::ParseBool(XmlAttribute* attr, bool defaultValue)
	{
		if (attr == 0) return defaultValue;
		char* value = attr->value();
		if (value == 0) return defaultValue;

		if (strstr(value, "true") != 0) return true;
		return false;
	}

	MEDIALOADERAPI Color XmlFile::ParseColor(XmlNode* node)
	{
		if (node == 0) return Color(1.0f);

		Color c(1.0f);
		XmlNode* child = 0;
		child = node->first_node("red");
		if (child != 0) c.r = XmlFile::ParseFloat(child, 1.0f);
		child = node->first_node("green");
		if (child != 0) c.g = XmlFile::ParseFloat(child, 1.0f);
		child = node->first_node("blue");
		if (child != 0) c.b = XmlFile::ParseFloat(child, 1.0f);

		return c;
	}
	MEDIALOADERAPI String XmlFile::Value(XmlAttribute* attr)
	{
		return attr != 0 ? String(attr->value()) : String();
	}

}