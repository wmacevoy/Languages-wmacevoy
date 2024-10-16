# regex_spec.rb
RSpec.describe 'Regular Expression for decimal literal' do
  let(:nonzero_decimal_digit) { /[1-9]/ }
  let(:decimal_digit) { /[0-9]/ }
  let(:octal_digit) {  /[0-7]/ }
  let(:hex_digit) {  /[0-9]|[A-F]|[a-f]/ }
  let(:binary_digit) {  /[0-1]/ }
  let(:decimal) { /#{nonzero_decimal_digit}('?#{decimal_digit}+)*/ }
  let(:size) { /[uU]?[lL]{0,2}/ }

  let(:pattern) { /^-?#{decimal}#{size}$/ }

  let(:should_pass) { [ "1", "-33'000", "4525235", "10'080", "123'456'789", "1ul", "1u", "1ll" ] }
  let(:should_fail) { ["'1'", "1'''3", "afed", "+33", "0", "ul", "lll", "3lll", "3uuull" ] }

  describe 'should pass' do
    it 'matches all expected strings' do
      should_pass.each do |str|
        expect(str).to match(pattern)
      end
    end
  end

  describe 'should fail' do
    it 'does not match any of the strings' do
      should_fail.each do |str|
        expect(str).not_to match(pattern)
      end
    end
  end
end
