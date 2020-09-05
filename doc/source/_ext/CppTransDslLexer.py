
from pygments.lexers.c_cpp import CppLexer
from pygments.token import Name, Keyword
from pygments.lexers import get_lexer_by_name  # refer LEXERS
from pygments.lexers._mapping import LEXERS

class CppTransDslLexer(CppLexer):
    EXTRA_KEYWORDS = set(('abcdefgs'))
    TYPE_KEYWORDS  = set(('ASSERT', 'abcdefg'))
    FUNC_KEYWORDS  = set(('__MACO_simple_repeat_from_0', '__MACO_if', '__MACO_eq',
                          '__MACO_loop', '__MACO_while', '__MACO_prev', '__MACO_next',
                          '__MACO_inc', '__MACO_dec', '__MACO_while', '__MACO_map',
                          '__MACO_num_of_args', '__MACO_ne', '__MACO_gt', '__MACO_gte',
                          '__MACO_make_index_seq', '__MACO_make_token_seq', '__MACO_map_i'))
    CONST_KEYWORDS = set(('whatsoever', 'abcdefg'))

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
