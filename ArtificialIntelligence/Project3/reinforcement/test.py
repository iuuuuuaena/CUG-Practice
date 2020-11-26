import random

print(random.choice([]))


def update(self, state, action, nextState, reward):
    """
      The parent class calls this to observe a
      state = action => nextState and reward transition.
      You should do your Q-Value update here

      NOTE: You should never call this function,
      it will be called on your behalf
    """
    "*** YOUR CODE HERE ***"
    self.qValues[(state, action)] = ((1 - self.alpha) * self.getQValue(state, action)) + self.alpha \
                                    * (reward + self.discount * self.computeValueFromQValues(nextState))


def computeValueFromQValues(self, state):
    """
      Returns max_action Q(state,action)
      where the max is over legal actions.  Note that if
      there are no legal actions, which is the case at the
      terminal state, you should return a value of 0.0.
    """
    "*** YOUR CODE HERE ***"
    if len(self.getLegalActions(state)) == 0:
        return 0.0
    max_value = -float('inf')
    for action in self.getLegalActions(state):
        max_value = max(max_value, self.getQValue(state, action))
    return max_value


def getQValue(self, state, action):
    """
      Returns Q(state,action)
      Should return 0.0 if we have never seen a state
      or the Q node value otherwise
    """
    "*** YOUR CODE HERE ***"
    return self.qValues[(state, action)]


def computeActionFromQValues(self, state):
    """
      Compute the best action to take in a state.  Note that if there
      are no legal actions, which is the case at the terminal state,
      you should return None.
    """
    "*** YOUR CODE HERE ***"
    legal_actions = self.getLegalActions(state)
    if len(legal_actions) == 0: return None
    values = [self.getQValue(state, action) for action in legal_actions]
    max_value = max(values)
    best_indices = [index for index in range(len(values)) if values[index] == max_value]
    return legal_actions[random.choice(best_indices)]


def getAction(self, state):
    """
      Compute the action to take in the current state.  With
      probability self.epsilon, we should take a random action and
      take the best policy action otherwise.  Note that if there are
      no legal actions, which is the case at the terminal state, you
      should choose None as the action.

      HINT: You might want to use util.flipCoin(prob)
      HINT: To pick randomly from a list, use random.choice(list)
    """
    # Pick Action
    legalActions = self.getLegalActions(state)
    action = None
    "*** YOUR CODE HERE ***"
    # util.raiseNotDefined()
    if random.random() < self.epsilon:
        action = random.choice(legalActions)
    else:
        action = self.getPolicy(state)
    return action
