PATCH = <<-C
#ifdef RUBY_PARSER_PRINT_TOKENS
    mri_tokenizer_print_token(&t);
#endif
C

def abort(message)
  $stderr.puts(message)
  exit 1
end

PARSE_Y_PATH = ENV.fetch('PARSE_Y_PATH') { abort("PARSE_Y_PATH env var must be provided") }
parse_y = File.read(PARSE_Y_PATH).lines

# 1. find definition of `yylex` function
line_idx = parse_y.find_index { |line| line.start_with?('yylex(') }
if line_idx.nil?
  abort('Failed to find declaration of yylex function')
end
# 2. find its 'return' statement
loop do
  line_idx += 1
  line = parse_y[line_idx]
  if line.nil?
    abort('Failed to find return statement of yylex function')
  end
  if line.include?('return')
    break
  end
end
# 3. go 1 line up
line_idx -= 1
# 4. append "\n<patch>"
parse_y[line_idx] += "\n#{PATCH}\n"
# 5. write patched code back to parse.y
File.write(PARSE_Y_PATH, parse_y.join)
