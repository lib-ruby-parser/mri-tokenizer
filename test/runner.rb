def abort(message)
  $stderr.puts(message)
  exit 1
end

mri_tokenizer = ENV.fetch('MRI_TOKENIZER') { abort('MRI_TOKENIZER variable is missing') }

expected_output = File.read('test/output')
actual_output = `#{mri_tokenizer} test/input`

if expected_output == actual_output
  puts 'OK'
else
  puts <<~MSG
Error:

Expected output:
#{expected_output}

Actual output:
#{actual_output}
MSG
end
