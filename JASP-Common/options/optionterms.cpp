
#include "optionterms.h"
#include <boost/foreach.hpp>

using namespace std;

OptionTerms::OptionTerms()
{
	_onlyOneComponent = false;
	_onlyOneTerm = false;
}

void OptionTerms::set(const Json::Value &value)
{
	if ( ! value.isArray())
		return;

	vector<vector<string> > terms;

	for (int i = 0; i < value.size(); i++)
	{
		const Json::Value &jVariable = value.get(i, Json::nullValue);
		if ( ! jVariable.isArray())
			return;

		vector<string> term;

		for (int j = 0; j < jVariable.size(); j++)
		{
			Json::Value jComponent = jVariable.get(j, Json::nullValue);
			if ( ! jComponent.isString())
				return;

			term.push_back(jComponent.asString());
		}

		terms.push_back(term);
	}

	setValue(terms);
}

OptionTerms::OptionTerms(bool onlyOneComponent, bool onlyOneTerm)
{
	_onlyOneComponent = onlyOneComponent;
	_onlyOneTerm = onlyOneTerm;
}

Json::Value OptionTerms::asJSON() const
{
	Json::Value top;

	BOOST_FOREACH(const vector<string> &term, _value)
	{
		Json::Value row(Json::arrayValue);

		BOOST_FOREACH(const string &component, term)
		{
			row.append(component);
		}

		top.append(row);
	}

	return top;
}

Option *OptionTerms::clone() const
{
	OptionTerms *c = new OptionTerms(_onlyOneComponent, _onlyOneTerm);
	c->setValue(value());
	return c;
}

void OptionTerms::init(const Json::Value &data)
{
	Json::Value def4ult = data.get("default", Json::nullValue);
	if (def4ult.isNull() == false)
		set(def4ult);
}

void OptionTerms::setValue(const vector<vector<string> > &value)
{
	vector<vector<string> > v = value;

	if (_onlyOneTerm && value.size() > 1)
	{
		v.erase(++v.begin(), v.end());

		if (_onlyOneComponent && _onlyOneTerm && v.front().size() > 1)
		{
			vector<string> &term = v.front();
			term.erase(++term.begin(), term.end());
		}
	}

	OptionI::setValue(value);
}

void OptionTerms::setValue(const vector<string> &value)
{
	vector<vector<string> > terms;

	BOOST_FOREACH(string variable, value)
	{
		vector<string> components;
		components.push_back(variable);
		terms.push_back(components);
	}

	setValue(terms);
}

void OptionTerms::setValue(const string &value)
{
	vector<string> term;
	vector<vector<string> > terms;

	term.push_back(value);
	terms.push_back(term);

	setValue(terms);
}

bool OptionTerms::onlyOneTerm() const
{
	return _onlyOneTerm;
}

bool OptionTerms::onlyOneComponent() const
{
	return _onlyOneComponent;
}
