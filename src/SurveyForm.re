open Belt;

let _ = [%bs.raw {|require('./index.css')|}];

let setValue = (questions: array(Survey.Question.t), value, id) =>
  questions->Array.map(q => q.id === id ? {...q, value} : q);

let remove = (questions: array(Survey.Question.t), id) =>
  questions->Array.keep(q => q.id !== id);

//TO SERVER
let toFormType = (t: Survey.Question.type_) =>
  switch (t) {
  | Open => "Open"
  | Closed(_) => "Closed"
  | Rate(_) => "Rate"
  };

let toAnswer = (a: Survey.Answer.t) =>
  Some({"answer": Some(a.value), "id": Some(a.id)});

let toAnswers = (t: Survey.Question.type_) =>
  switch (t) {
  | Open => Some([||])
  | Closed(answers)
  | Rate(answers) => Some(answers->Array.map(toAnswer))
  };

let mapQuestion = (q: Survey.Question.t) =>
  Some({
    "question": q.value,
    "formType": toFormType(q.type_),
    "answers": toAnswers(q.type_),
  });

let mapQuestions = questions => Some(questions->Array.map(mapQuestion));

//FROM SERVER
let fromAnswer: 'a => Survey.Answer.t =
  a => {
    value: a->Option.flatMap(a => a##answer)->Option.getWithDefault(""),
    id: a->Option.flatMap(a => a##id)->Option.getWithDefault(""),
  };

let fallbackToOpenType = a => {
  switch (a) {
  | Some(a) => a
  | None => "Open"
  };
};

let fromType = (s, answers) =>
  Survey.Question.(
    switch (s) {
    | "Closed" =>
      Closed(
        answers
        ->Option.map(a => a->Array.map(fromAnswer))
        ->Option.getWithDefault([||]),
      )
    | "Rate" =>
      Rate(
        answers
        ->Option.map(a => a->Array.map(fromAnswer))
        ->Option.getWithDefault([||]),
      )
    | "Open"
    | _ => Open
    }
  );

let fromPlaceholder = s =>
  switch (s) {
  | "Rate" => Survey.Question.openPlaceholder
  | "Closed" => Survey.Question.openPlaceholder
  | "Open"
  | _ => Survey.Question.openPlaceholder
  };
let fromQuestion: 'a => Survey.Question.t =
  q => {
    id: q##_id,
    value: q##question,
    type_: fromType(q##formType, q##answers),
    placeholder: q##formType->fromPlaceholder,
  };

let fromQuestions = questions => questions->Array.map(fromQuestion);

[@react.component]
let make =
    (
      ~name,
      ~setName,
      ~desc,
      ~setDesc,
      ~questions: array(Survey.Question.t),
      ~setQuestions,
      ~request=?,
      ~fetching,
    ) => {
  <>
    <div
      className={
        TW.[
          FontSize(Text3xl),
          Position(Sticky),
          Placement(Top0),
          Display(Flex),
          AlignItems(ItemsCenter),
          ZIndex(Z50),
          Height(H16),
          Width(TW.W8_12),
        ]
        ->TW.make
      }>
      <Text className=TW.[FontSize(Text2xl), Margin(Mr4)]>
        {j|Nowa ankieta:|j}
      </Text>
      <Input
        value=name
        onChange={value => setName(_ => value)}
        className=TW.[Width(TW.W6_12), FontSize(Text2xl)]
        placeholder="Nazwa ankiety"
      />
      {request
       ->Option.map(r =>
           <Button
             loading=fetching
             onClick={_ =>
               r()
               |> Js.Promise.then_(_ => {
                    ReasonReactRouter.push("/surveys");
                    Js.Promise.resolve();
                  })
               |> ignore
             }>
             <Text color=`white> {j|Utwórz ankietę|j} </Text>
           </Button>
         )
       ->Option.getWithDefault(React.null)}
    </div>
    <div className={[Height(H8)]->TW.make} />
    <div>
      <Text className=TW.[FontSize(TextXl), Margin(Mr4)]>
        {j|Krótki opis:|j}
      </Text>
      <Input
        value=desc
        onChange={value => setDesc(_ => value)}
        className=TW.[Width(TW.W6_12), FontSize(TextXl)]
        placeholder={j|Wprowadź opis|j}
      />
    </div>
    <div className={[Height(H8)]->TW.make} />
    <Animation.Presence>
      {questions
       ->Array.mapWithIndex((index, q) =>
           <div>
             {switch (q.type_) {
              | Open =>
                <OpenQuestion
                  index
                  placeholder={q.placeholder}
                  key={q.id}
                  value={q.value}
                  onChange={v =>
                    setQuestions(questions => setValue(questions, v, q.id))
                  }
                  onDelete={() =>
                    setQuestions(questions => remove(questions, q.id))
                  }
                />

              | Rate(answers)
              | Closed(answers) =>
                <CloseQuestion
                  index
                  key={q.id}
                  placeholder={q.placeholder}
                  value={q.value}
                  onChange={v =>
                    setQuestions(questions => setValue(questions, v, q.id))
                  }
                  onDelete={() =>
                    setQuestions(questions => remove(questions, q.id))
                  }
                  onChangeAnswer={(answerId, v) =>
                    setQuestions(questions =>
                      Survey.Question.changeAnswer(
                        ~questions,
                        ~questionId=q.id,
                        ~answerId,
                        ~value=v,
                      )
                    )
                  }
                  onAddAnswer={() =>
                    setQuestions(questions =>
                      Survey.Question.addAnswer(questions, q.id)
                    )
                  }
                  onDeleteAnswer={answerId =>
                    setQuestions(questions =>
                      Survey.Question.removeAnswer(
                        ~answerId,
                        ~questionId=q.id,
                        questions,
                      )
                    )
                  }
                  answers
                />
              }}
           </div>
         )
       ->React.array}
    </Animation.Presence>
    <Button onClick={_ => setQuestions(Survey.Question.add(_, Open))}>
      <Text color=`white> {j|Dodaj pytanie otwarte|j} </Text>
    </Button>
    <Button
      onClick={_ => setQuestions(Survey.Question.add(_, Closed([||])))}>
      <Text color=`white> {j|Dodaj pytanie zamknięte|j} </Text>
    </Button>
    <Button onClick={_ => setQuestions(Survey.Question.add(_, Rate([||])))}>
      <Text color=`white> {j|Dodaj pytanie z oceną|j} </Text>
    </Button>
  </>;
};