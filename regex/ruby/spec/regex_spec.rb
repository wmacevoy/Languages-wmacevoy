# regex_spec.rb
RSpec.describe 'Regular Expression Matcher' do
  let(:pattern) { /^\d{3}-\d{2}-\d{4}$/ }
  let(:should_pass) { ['123-45-6789', '001-02-0034'] }
  let(:should_fail) { ['123-456-789', 'abcd-ef-ghij', '123456789'] }

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
