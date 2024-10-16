# regex_spec.rb
RSpec.describe 'Regular Expression Matcher for letter' do
  let(:pattern) { /^\p{L}$/ }
  let(:should_pass) { ['A', 'a', 'Δ'] }
  let(:should_fail) { ['1', '*', '_'] }

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

RSpec.describe 'Regular Expression Matcher for _' do
  let(:pattern) { /^_$/ }
  let(:should_pass) { ['_'] }
  let(:should_fail) { ['1', '*', 'A'] }

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

RSpec.describe 'Regular Expression Matcher for _ or letter' do
  let(:pattern) { /^(_|\p{L})$/ }
  let(:should_pass) { ['_','A','x','Δ'] }
  let(:should_fail) { ['1','*'] }

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


RSpec.describe 'Regular Expression Matcher for _ or letter or 0..9' do
  let(:pattern) { /^(_|\p{L}|[0-9])$/ }
  let(:should_pass) { ['_','A','x','Δ','1'] }
  let(:should_fail) { ['*'] }

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

# Turns out ruby does allow composition...

RSpec.describe 'Regular Expression Matcher C++ id' do
  let(:letter) { /\p{L}/ }
  let(:digit) { /[0-9]/ }
  let(:underscore) { /_/ }
  let(:id_start) { /(#{letter}|#{underscore})/ }
  let(:id_after) { /(#{letter}|#{underscore}|#{digit})/ }
  let(:id) { /#{id_start}#{id_after}*/ }

  let(:pattern) { /^#{id}$/ }
  let(:should_pass) { ['_','A','my_id','Δx3','CamelCase'] }
  let(:should_fail) { ['*','1', '1x','' ] }

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
