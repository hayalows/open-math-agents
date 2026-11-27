# Research coordination — START HERE

Owner: @hayalows. Updated 2026-11-27 16:29 UTC.
This branch is the shared, GitHub-readable entry point for Codex, DeepSeek and mobile ChatGPT. It is for coordination and research artifacts, NOT an upstream proof submission. Do not merge this branch into upstream.

## Today's goal

Resolve one genuinely open mathematical problem if possible. Prioritize a complete, rigorously checkable proof or counterexample over repeated reviews, statement-only submissions and leaderboard activity. A research breakthrough is not guaranteed.

Read the current [official contribution protocol](https://lefttosolve.com/join.txt), [upstream instructions](https://github.com/GuillaumeBAUD-coder/open-math-agents/blob/main/CONTRIBUTING_AGENTS.md), and live [profile](https://lefttosolve.com/a/hayalows). Verify live task availability, prior literature, and existing submissions before claiming. Do not duplicate work.

## Current tasks (recheck on arrival)

| Agent | Task | State |
|---|---|---|
| Codex | A116150 | Acknowledged TODAY-FOCUS at 16:28 UTC; working on a bounded prime search with compositeness evidence. |
| DeepSeek | Arxiv.1609.08688.maximalLength_le_isBigO.R1.H2 | Last confirmed separate assignment at 16:13 UTC; check latest status. |
| Mobile ChatGPT | Targeted mathematical support and coordination | Avoid duplicating the Codex search. |
| A045473 | Statement PR #7582 | Compilation accepted; human review and merge pending at last check. Ordinary proof available; full formal proof unchecked. |

### Codex: A116150

[Exact problem](https://lefttosolve.com/p/OeisA116150.conjecture), [OEIS sequence](https://oeis.org/A116150). Find the next prime term after index 431 of S_n = sum from j=1 to n of (3^j + (-2)^j). Verify the exact pinned Lean statement and legitimate question-value submission procedure. Compute by recurrence or by the identity 6*S_n = 3^(n+2) - 2*(-2)^(n+1) - 13. Even indices are composite for n>=2. Sieve odd indices, record checkable factors or compositeness witnesses, and establish rigorous primality and minimality if a candidate appears. Probable primes and finite negative searches are not completed solutions. Use a bounded first attempt and switch to another eligible full problem if the target becomes unproductive; avoid repeated task churn. Record precise limits and evidence.

### A045473: proof materials for later submission

- [Statement PR and review comment](https://github.com/GuillaumeBAUD-coder/open-math-agents/pull/7582#issuecomment-7223302025)
- [Codex's research, fixed commit](https://github.com/hayalows/open-math-agents/tree/8383bf537f53efeecd842c637dd513c90b26a968/research/oeis-a045473)
- The ordinary proof uses Phi_7(X+1), the finite-field cyclotomic factor degree theorem, order modulo 7, and the separate characteristic-7 case.
- The modulo-seven lemma was reported checked by Codex with Lean 4.36.0. The full Lean draft is not yet verified against the project's pinned version.
- Do not add extra research files to the statement PR or submit the proof until the applicable project requirements are met. Once eligible, claim the proof target and submit a separate compliant proof PR. No unnecessary repeated review before that.

## Workflow

1. Read this page and the latest agent reports in this branch. Check live desk status, pinned upstream statement, and current PRs.
2. Choose a distinct target and agent ID, use a clean isolated branch/worktree, and respect existing agents' files. Follow the official claim, heartbeat, submission and release process.
3. Run exact tests, research relevant results and write rigorous arguments. Use the pinned Lean environment and checker; inspect the actual verdict, not simply green GitHub Actions. No unapproved axioms, sorry in proofs, or prohibited verification shortcuts.
4. Publish eligible mathematical submissions to the official project using its required format. One new contribution file per PR. Never add coordination files to these PRs.
5. Save a short report under reports/agents/<unique-UTC-timestamp>-<agent>.md on coordination/research. Include task, assignment status (no lease token), evidence, reproducible commands, PR/commit links, verification result, and next action. Use one file per session and avoid overwriting others' reports. Keep this index updated only when priorities change.
6. The local .oma directory is intentionally gitignored. Agents on the owner's desktop may also use its local START-HERE.md and research handoffs, but this tracked GitHub page is the portable entry point. Never publish private session logs, credentials, lease tokens, personal filesystem paths or unrelated work.

Spend usage on actual mathematical progress, not repeated summaries. No paid compute, destructive changes or unrelated publications without the owner's approval. Do not claim results without evidence.
