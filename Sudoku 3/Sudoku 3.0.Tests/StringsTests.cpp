// Danylo Fitel 2026
// Unit tests for Strings: every string exists in every language, and translations agree on
// their format placeholders. Strings::Get falls back to an empty string for a missing case,
// so without these checks a forgotten translation would silently show as a blank label.

#include "Strings.h"

using namespace System;
using namespace Sudoku_3_0;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace Sudoku_3_0_Tests
{
    [TestClass]
    public ref class StringsTests
    {
    private:
        // StringId and Language are native enums, so their values cannot be enumerated by
        // reflection: string IDs run 0 .. StringId::Count - 1, and the languages are listed here.
        static array<Language>^ AllLanguages()
        {
            return gcnew array<Language>{ Language::English, Language::Ukrainian };
        }

        static String^ Name(StringId id, Language lang)
        {
            return "StringId " + ((unsigned int)id).ToString() + " in language " + ((unsigned int)lang).ToString();
        }

    public:
        [TestMethod]
        void EveryString_IsTranslatedInEveryLanguage()
        {
            for (unsigned int i = 0; i < (unsigned int)StringId::Count; ++i)
            {
                StringId id = static_cast<StringId>(i);
                for each (Language lang in AllLanguages())
                    Assert::IsFalse(String::IsNullOrEmpty(Strings::Get(id, lang)), "Missing text for " + Name(id, lang));
            }
        }

        [TestMethod]
        void Translations_HaveTheSamePlaceholders()
        {
            // A translation that drops or adds {0}/{1} would format wrongly or throw at runtime
            for (unsigned int i = 0; i < (unsigned int)StringId::Count; ++i)
            {
                StringId id = static_cast<StringId>(i);
                String^ english = Strings::Get(id, Language::English);
                for each (Language lang in AllLanguages())
                {
                    String^ text = Strings::Get(id, lang);
                    for (int n = 0; n <= 3; ++n)
                    {
                        String^ placeholder = "{" + n.ToString() + "}";
                        Assert::AreEqual(english->Contains(placeholder), text->Contains(placeholder),
                            Name(id, lang) + " disagrees with English on " + placeholder);
                    }
                }
            }
        }

        [TestMethod]
        void Count_IsPastTheLastString()
        {
            // Documents the fallback the tests above guard against: Count itself has no text
            Assert::AreEqual(String::Empty, Strings::Get(StringId::Count, Language::English));
        }
    };
}
