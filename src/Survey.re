open Belt;

let makeId: unit => string = [%bs.raw
  {|
 function() {
  return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
    var r = Math.random() * 16 | 0, v = c == 'x' ? r : (r & 0x3 | 0x8);
    return v.toString(16);
  });
}

|}
];

module Answer = {
  type t = {
    id: string,
    value: string,
    isCorrect: bool,
  };

  let make = () => {id: makeId(), value: "", isCorrect: false};

  let add = answers => answers->Array.concat([|make()|]);

  let remove = (answerId, answers) =>
    answers->Array.keep(a => a.id !== answerId);

  let change = (~answerId, ~answers, ~value) =>
    answers->Array.map(a => a.id === answerId ? {...a, value} : a);
};

module Question = {
  type type_ =
    | Open
    | Closed(array(Answer.t));

  type t = {
    id: string,
    value: string,
    type_,
  };

  let make = type_ =>
    switch (type_) {
    | Open => {id: makeId(), value: "", type_}
    | Closed(_) => {
        id: makeId(),
        value: "",
        type_: Closed([|Answer.make()|]),
      }
    };

  let add = (questions, type_) => questions->Array.concat([|make(type_)|]);

  let addAnswer = (questions, questionId) =>
    questions->Array.map(q =>
      switch (q.type_, q.id === questionId) {
      | (Closed(answers), true) => {
          ...q,
          type_: Closed(answers->Answer.add),
        }
      | (_, _) => q
      }
    );

  let changeAnswer = (~questions, ~questionId, ~answerId, ~value) =>
    questions->Array.map(q =>
      switch (q.type_, questionId === q.id) {
      | (Closed(answers), true) => {
          ...q,
          type_: Closed(Answer.change(~answers, ~answerId, ~value)),
        }
      | (_, _) => q
      }
    );

  let removeAnswer = (~answerId, ~questionId, questions) =>
    questions
    ->Array.map(q =>
        switch (q.type_, q.id === questionId) {
        | (Closed(answers), true) => {
            ...q,
            type_: Closed(Answer.remove(answerId, answers)),
          }
        | (_, _) => q
        }
      )
    ->Array.keep(q =>
        switch (q.type_) {
        | Closed([||]) => false
        | _ => true
        }
      );
};