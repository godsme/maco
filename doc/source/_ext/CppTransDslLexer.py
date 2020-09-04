
from pygments.lexers.c_cpp import CppLexer
from pygments.token import Name, Keyword
from pygments.lexers import get_lexer_by_name  # refer LEXERS
from pygments.lexers._mapping import LEXERS

class CppTransDslLexer(CppLexer):
    EXTRA_KEYWORDS = set(('__sync'))
    FUNC_KEYWORDS  = set(('exec'))
    TYPE_KEYWORDS  = set(('__MACO_simple_iterator_from_0', '__MACO_if', '__MACO_eq', '__MACO_loop', '__MACO_while'
                          '__MACO_prev', '__MACO_next', '__MACO_inc', '__MACO_dec'))
    CONST_KEYWORDS = set(('ASSERT'))

    def get_tokens_unprocessed(self, text):
        for index, token, value in CppLexer.get_tokens_unprocessed(self, text):
            if token is Name and value in self.EXTRA_KEYWORDS:
                yield index, Keyword, value
            elif token is Name and value in self.FUNC_KEYWORDS:
                yield index, Name.Function, value
            elif token is Name and value in self.TYPE_KEYWORDS:
                yield index, Name.Class, value
            elif token is Name and value in self.CONST_KEYWORDS:
                yield index, Name.Constant, value
            else:
                yield index, token, value


def setup(app):
    app.add_lexer('c++', CppTransDslLexer)
