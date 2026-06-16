# Global AGENTS.md

## Core Principles

* Prioritize correctness over speed.
* Prefer simple, maintainable solutions over clever ones.
* Avoid unnecessary complexity and dependencies.
* Do not make assumptions about requirements.
* Ask for clarification when requirements are ambiguous.

---

## Before Making Changes

* Read relevant files before modifying them.
* Understand the existing architecture and coding style.
* Search for existing implementations before creating new ones.
* Reuse existing utilities and components whenever possible.

---

## Code Quality

* Write clean, readable, and maintainable code.
* Follow language-specific best practices.
* Use descriptive variable and function names.
* Avoid magic numbers and hardcoded values.
* Keep functions focused on a single responsibility.
* Prefer composition over duplication.

---

## Documentation

* Add comments only when necessary.
* Explain why, not what.
* Update documentation when behavior changes.
* Keep README files accurate and current.

---

## Security

* Never expose secrets, API keys, passwords, or tokens.
* Use environment variables for sensitive configuration.
* Validate all external input.
* Follow the principle of least privilege.
* Do not introduce known security vulnerabilities.

---

## Testing

* Write tests for new functionality whenever practical.
* Update existing tests when behavior changes.
* Do not remove failing tests without understanding the cause.
* Verify changes before marking tasks complete.

---

## Debugging

* Identify root causes instead of patching symptoms.
* Reproduce issues before attempting fixes.
* Explain findings clearly.
* Prefer permanent fixes over temporary workarounds.

---

## Dependencies

* Minimize new dependencies.
* Prefer standard library solutions when reasonable.
* Evaluate maintenance, security, and necessity before adding packages.
* Remove unused dependencies when discovered.

---

## Git Practices

* Make focused, atomic changes.
* Avoid unrelated modifications.
* Preserve existing user work.
* Do not overwrite user changes without explicit instruction.

---

## Refactoring

* Improve code incrementally.
* Preserve existing functionality unless instructed otherwise.
* Reduce duplication when encountered.
* Maintain backward compatibility when reasonable.

---

## AI Agent Behavior

* Explain major decisions before making large changes.
* Be transparent about uncertainty.
* Do not fabricate results, tests, or benchmarks.
* Clearly distinguish facts from assumptions.
* If a task cannot be completed, explain why.

---

## Performance

* Optimize only after correctness.
* Consider scalability for frequently executed code.
* Avoid premature optimization.
* Measure before claiming performance improvements.

---

## Project Discovery

When entering a new repository:

1. Read README.md.
2. Inspect project structure.
3. Identify build and run commands.
4. Identify test framework.
5. Identify dependency management system.
6. Understand coding conventions before editing.

---

## Default Output Expectations

* Production-quality code.
* Minimal but sufficient documentation.
* Clear explanations.
* Safe changes.
* Maintainable architecture.
* Consistent formatting.
