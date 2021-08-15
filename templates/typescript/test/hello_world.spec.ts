import { expect } from 'chai';
import { describe, it } from 'mocha';
import hello from '../src/hello_world';

describe('Hello function', () => {
  it('should return hello world', () => {
    const result = hello('world');
    expect(result).to.equal('Hello world! ');
  });
});
